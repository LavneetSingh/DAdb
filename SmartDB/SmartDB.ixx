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

	#pragma region Data Node
		template <typename T>
		struct DNod
		{
			unique_ptr<T> data;
			shared_ptr<DNod> next;
		};
	#pragma endregion

	#pragma region RBTree Node
		template<typename T>
		struct TNod
		{
			weak_ptr<DNod<T>> dbNod;
			unique_ptr<TNod<T>> left;
			unique_ptr<TNod<T>> right;
		};

	#pragma endregion

	export template <typename T>
	class SmartDB
	{
        #pragma region Ctor
	public:
		explicit SmartDB ( unique_ptr<T> obj )
		{
			//last = db = make_shared<DNod<T>> ();
			last = db = shared_ptr<DNod<T>> ( new DNod<T> () );
			last->data = std::move ( obj );
			last->next = nullptr;
			s = 1;
		}
        #pragma endregion

		#pragma region Database Layer
		size_t insert ( unique_ptr<T> obj )
		{
			last->next = shared_ptr<DNod<T>> ( new DNod<T> () );
			last->next->data = std::move ( obj );
			last->next->next = nullptr;
			last = last->next;

			return ++s;
		}
		unique_ptr<T> remove ( function<bool ( const unique_ptr<T>& )> comparer )
		{
			auto itr = db;
			shared_ptr<DNod<T>> itrPrev = nullptr;
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

	private:
		shared_ptr<DNod<T>> db;
		shared_ptr<DNod<T>> last;
		size_t s;
		//map<string, shared_ptr<TNod<T>>> indices;
	};
}

//namespace In
//{
//	using namespace std;
//	template<typename T>
//	struct DNod
//	{
//		T data;
//		shared_ptr<T> next;
//	};
//}