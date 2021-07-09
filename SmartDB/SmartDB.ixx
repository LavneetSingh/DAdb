module;
#include <concepts>
#include <string>
#include <functional>
#include <memory>
#include <map>

export module SmartDB;

namespace DAdb
{
	using namespace std;
	
	template <typename T>
	using Comparer = function<int ( const unique_ptr<T>&, const unique_ptr<T>& )>;

	#pragma region Data Node
		template <typename T>
		struct DNode
		{
			unique_ptr<T> data;
			shared_ptr<DNode> next;
		};
	#pragma endregion

	#pragma region RBTree Node
		template<typename T>
		struct TNode
		{
			weak_ptr<DNode<T>> dbNode;
			unique_ptr<TNode<T>> left;
			unique_ptr<TNode<T>> right;
		};

	#pragma endregion

	export template <typename T>
	class SmartDB
	{
        #pragma region Ctor
	public:
		explicit SmartDB ( unique_ptr<T> obj )
		{
			//last = db = make_shared<DNode<T>> ();
			last = db = shared_ptr<DNode<T>> ( new DNode<T> () );
			last->data = std::move ( obj );
			last->next = nullptr;
			s = 1;
		}
        #pragma endregion

		#pragma region Database Layer
		size_t insert ( unique_ptr<T> obj )
		{
			last->next = shared_ptr<DNode<T>> ( new DNode<T> () );
			last->next->data = std::move ( obj );
			last->next->next = nullptr;
			last = last->next;

			return ++s;
		}
		unique_ptr<T> remove ( function<bool ( const unique_ptr<T>& )> comparer )
		{
			auto itr = db;
			shared_ptr<DNode<T>> itrPrev = nullptr;
			do
			{
				if ( comparer ( itr->data ) )
					break;
				itrPrev = itr;
				itr = itr->next;

			} while ( itr );

			if ( itr )
			{
				if ( itrPrev == nullptr )
				{
					db = itr->next;
				}
				else
				{
					itrPrev->next = itr->next;
					itr->next = nullptr;
				}
				--s;
				return std::move ( itr->data );
			}

			return nullptr;
		}
#if _DEBUG
		size_t getAll ( std::vector<T*>& r ) const
		{
			auto itr = db;
			while ( itr )
			{
				r.push_back ( itr->data.get () );
				itr = itr->next;
			}

			return s;
		}

		size_t count () const
		{
			return s;
		}
#endif
#pragma endregion

        #pragma region Database Indexing / Search
		bool createIndex ( string indexID, Comparer<T> comparer )
		{
			auto itr = db;
			auto root = createTNode ( itr );
			indices.insert ( make_pair(indexID, std::move(root)));
			itr = itr->next;

			while ( itr != nullptr )
			{
				auto newNode = createTNode ( itr );
				placeNodeInTree ( std::move(newNode), indices[indexID], comparer );
				itr = itr->next;
			}

			return true;
		}
#pragma endregion
	private:
		unique_ptr<TNode<T>> createTNode (weak_ptr<DNode<T>> dbNode)
		{
			auto n = make_unique<TNode<T>> ();
			n->dbNode = dbNode;

			return std::move ( n );
		}
		unique_ptr<TNode<T>> placeNodeInTree (unique_ptr<TNode<T>> tNode, unique_ptr<TNode<T>>& root, Comparer<T> comparer )
		{
			if ( root == nullptr )
				return tNode;

			if ( comparer(tNode->dbNode.lock()->data, root->dbNode.lock()->data ) > 0 )
			{
				auto n = placeNodeInTree ( std::move(tNode), root->right, comparer );
				if ( n != nullptr )
					root->right = std::move(n);
			}
			else
			{
				auto n = placeNodeInTree ( std::move(tNode), root->left, comparer );
				if ( n != nullptr )
					root->left = std::move(n);
			}
			return nullptr;
		}

	private:
		shared_ptr<DNode<T>> db;
		shared_ptr<DNode<T>> last;
		size_t s;
		map<string, unique_ptr<TNode<T>>> indices;
	};
}

//namespace In
//{
//	using namespace std;
//	template<typename T>
//	struct DNode
//	{
//		T data;
//		shared_ptr<T> next;
//	};
//}