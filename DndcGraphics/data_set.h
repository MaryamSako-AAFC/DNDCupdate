
#ifndef  DATA_SET_H
#define  DATA_SET_H


/*!
  \file data_set.h

  \brief
    Defines the ElkhornData and DataSet classes.

  $Id$

  \author Steven Knight
*/

#include <vector>

/*! \brief enum for ElkhornDataTypes */
typedef enum ElkhornDataType { dSOC, CH4, N2O, NO, N2, NH3, N_leaching, TOTAL_SIZE, NOT_DEFINED };

/*! \brief */
typedef std::vector< double > DataList;

/*! */
class ElkhornBinData
{
    public:

        ElkhornBinData( int c = 0, double l = 0.0, double r = 0.0 );
        ElkhornBinData& operator=( const ElkhornBinData& db );

        int count;
        double left;
        double right;
        DataList list;

        friend std::ostream& operator<<( std::ostream& os, const ElkhornBinData& bd );

};

typedef std::vector< ElkhornBinData > ElkhornBinDataList;

/*! */
class ElkhornData
{
    public:
        ElkhornData( ElkhornDataType type = NOT_DEFINED, std::string title = "" );
        /*! \brief Contains the data from parsing the file */
        DataList parse_data;

        /*! \brief Contains the data for the histogram */
        ElkhornBinDataList bin_data_list;

        friend std::ostream& operator<<( std::ostream& os, const ElkhornData & d );

        std::string data_set_title;
        ElkhornDataType data_set_type;
};

    

typedef std::vector< ElkhornData > ElkhornDataSet;

/*! */
class DataSet
{
    public:
        DataSet();
        ElkhornDataSet data_set;
};

#endif   /* ----- #ifndef DATA_SET_H  ----- */
