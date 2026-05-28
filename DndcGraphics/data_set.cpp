

#include "stdafx.h"


/*!
  \file data_set.cpp

  \brief

  $Id$

  \author Steven Knight
*/

#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
#include "data_set.h"

ElkhornData::ElkhornData( ElkhornDataType type, std::string title ) 
{
    data_set_type = type;
    data_set_title = title;
}

DataSet::DataSet()
{
    /* ensure data_set is large enough */
    data_set.resize( TOTAL_SIZE );

    /* set the type foreach element in data_set */
    data_set[ dSOC ] = ElkhornData( dSOC, "dSOC");
    data_set[ CH4 ] = ElkhornData( CH4, "CH4"  );
    data_set[ N2O ] = ElkhornData( N2O, "N2O" );
    data_set[ NO ] = ElkhornData( NO, "NO" );
    data_set[ N2 ] = ElkhornData( N2, "N2" );
    data_set[ NH3 ] = ElkhornData( NH3, "NH3" );
    data_set[ N_leaching ] = ElkhornData( N_leaching, "N_leaching" );
}

/* ElkhornBinData */

ElkhornBinData::ElkhornBinData( int c, double l, double r )
{
    count = c;
    left = l;
    right = r;
}

ElkhornBinData& ElkhornBinData::operator=( const ElkhornBinData& bd )
{
    if ( this == &bd )
    {
        this->count = bd.count;
        this->left = bd.left;
        this->right = bd.right;
        this->list = bd.list;
    }

    return *this;
}

std::ostream& operator<<( std::ostream& os, const ElkhornBinData& bd )
{
    os << "        Count = " << bd.count << "\n";
    os << "         Left = " << bd.left << "\n";
    os << "        Right = " << bd.right << "\n";
    os << "         Size = " << bd.list.size() << "\n";
    os << "Data Elements = ";
    //copy( bd.list.begin(), bd.list.end(), std::ostream_iterator< double >( os, "\t" ) );
    os << "\n";
    return os;
}

/* ElkhornData */

std::ostream& operator<<( std::ostream& os, const ElkhornData & d )
{
    //copy( d.bin_data_list.begin(), d.bin_data_list.end(), std::ostream_iterator< ElkhornBinData >( os, "\n\n" ) );
    return os;
}