#include "pch.h"
#include <memory>
import SmartDB;
namespace DBTests
{
	TEST ( InsertToDB, InsertOne ) {
		auto a = std::make_unique<int> ( 1 );
		DAdb::SmartDB<int> db ( std::move ( a ) );

		EXPECT_TRUE ( db.count () == 1 );
	}
	TEST ( InsertToDB, InsertInts ) {
		auto a = std::make_unique<int> ( 1 );
		DAdb::SmartDB<int> db ( std::move ( a ) );
		auto r2 = db.insert ( std::make_unique<int> ( 2 ) );
		auto r3 = db.insert ( std::make_unique<int> ( 3 ) );
		auto r4 = db.insert ( std::make_unique<int> ( 4 ) );
		auto r5 = db.insert ( std::make_unique<int> ( 5 ) );
		EXPECT_TRUE ( r2 == 2 && r3 == 3 && r4 == 4 && r5 == 5 );
	}
	TEST ( RemoveFromDB, RemoveOne )
	{
		DAdb::SmartDB<int> db ( std::make_unique<int> ( 1 ) );
		db.insert ( std::make_unique<int> ( 2 ) );
		db.insert ( std::make_unique<int> ( 3 ) );
		db.insert ( std::make_unique<int> ( 4 ) );
		db.insert ( std::make_unique<int> ( 5 ) );
		auto up = db.remove ( [] ( const std::unique_ptr<int>& t ){ return *t == 3; } );
		EXPECT_TRUE ( *up == 3 );
#ifdef _DEBUG
		std::vector<int*> v;
		auto c = db.getAll ( v );
		EXPECT_TRUE ( c == 4 );
		EXPECT_TRUE ( *v[0] == 1 );
		EXPECT_TRUE ( *v[1] == 2 );
		EXPECT_TRUE ( *v[2] == 4 );
		EXPECT_TRUE ( *v[3] == 5 );
#endif
	}
	TEST ( RemoveFromDB, RemoveFirst )
	{
		DAdb::SmartDB<int> db ( std::make_unique<int> ( 1 ) );
		db.insert ( std::make_unique<int> ( 2 ) );
		db.insert ( std::make_unique<int> ( 3 ) );
		db.insert ( std::make_unique<int> ( 4 ) );
		db.insert ( std::make_unique<int> ( 5 ) );
		auto up = db.remove ( [] ( const std::unique_ptr<int>& t ){ return *t == 1; } );
		EXPECT_TRUE ( *up == 1 );
#ifdef _DEBUG
		std::vector<int*> v;
		auto c = db.getAll ( v );
		EXPECT_TRUE ( c == 4 );
		EXPECT_TRUE ( *v[0] == 2 );
		EXPECT_TRUE ( *v[1] == 3 );
		EXPECT_TRUE ( *v[2] == 4 );
		EXPECT_TRUE ( *v[3] == 5 );
#endif
	}
	TEST ( RemoveFromDB, RemoveLast )
	{
		DAdb::SmartDB<int> db ( std::make_unique<int> ( 1 ) );
		db.insert ( std::make_unique<int> ( 2 ) );
		db.insert ( std::make_unique<int> ( 3 ) );
		db.insert ( std::make_unique<int> ( 4 ) );
		db.insert ( std::make_unique<int> ( 5 ) );
		auto up = db.remove ( [] ( const std::unique_ptr<int>& t ){ return *t == 5; } );
		EXPECT_TRUE ( *up == 5 );
#ifdef _DEBUG
		std::vector<int*> v;
		auto c = db.getAll ( v );
		EXPECT_TRUE ( c == 4 );
		EXPECT_TRUE ( *v[0] == 1 );
		EXPECT_TRUE ( *v[1] == 2 );
		EXPECT_TRUE ( *v[2] == 3 );
		EXPECT_TRUE ( *v[3] == 4 );
#endif
	}
	TEST ( RemoveFromDB, RemoveAll )
	{
		DAdb::SmartDB<int> db ( std::make_unique<int> ( 1 ) );
		db.insert ( std::make_unique<int> ( 2 ) );
		db.insert ( std::make_unique<int> ( 3 ) );
		auto up1 = db.remove ( [] ( const std::unique_ptr<int>& t ){ return *t == 1; } );
		EXPECT_TRUE ( *up1 == 1 );
		auto up2 = db.remove ( [] ( const std::unique_ptr<int>& t ){ return *t == 2; } );
		EXPECT_TRUE ( *up2 == 2 );
		auto up3 = db.remove ( [] ( const std::unique_ptr<int>& t ){ return *t == 3; } );
		EXPECT_TRUE ( *up3 == 3 );
#ifdef _DEBUG
		std::vector<int*> v;
		auto c = db.getAll ( v );
		EXPECT_TRUE ( c == 0 );
		EXPECT_TRUE ( v.size() == 0 );
		EXPECT_TRUE ( db.count () == 0 );
#endif
	}


	//TEST ( CreateIndex, NewIndex ) {
	//	DAdb::SmartDB<int> db;
	//	int i = 10, j = 20;
	//	auto result = db.createIndex ( "testIndex", [=] (int x, int y) {return 1; } );
	//	EXPECT_TRUE ( result );
	//}
	//TEST ( CreateGraph, NewGraph ) {
	//	DAdb::SmartDB<int> db;
	//	int i = 10;
	//	auto result = db.createGraph ( "testGraph",  std::move(i));
	//	EXPECT_TRUE ( result );
	//}
	//TEST ( ConnectGraphNodes, ConnectTwoNodes ) {
	//	DAdb::SmartDB<int> db;
	//	int i = 10, j = 20;
	//	auto result = db.createGraph ( "testGraph", std::move ( i ) );
	//	auto result = db.connectNodesInGraph ( "testGraph", j);
	//	EXPECT_TRUE ( result );
	//}


}