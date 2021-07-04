#include <iostream>
#include <memory>
import SmartDB;

int main ()
{
    DAdb::SmartDB<int> db(std::make_unique<int>(11));

    db.insert ( std::make_unique<int> ( 22 ) );
    auto v = db.insert ( std::make_unique<int> ( 33 ) );

    if ( v == 3 )
        std::cout <<" correct ";
}
