#ifdef ES

#ifndef  GRAPH_MAKER_H
#define  GRAPH_MAKER_H

#include <string>
#include "data_set.h"

#include "gd.h"
#include "gdfontt.h"
#include "gdfonts.h"
#include "gdfontmb.h"
#include "gdfontl.h"
#include "gdfontg.h"


/*!
  \file graph-maker.h

  \brief

  $Id$

  \author Steven Knight
*/
const std::string output_filename_ext = ".jpg";
const int width = 432;
const int height = 216;

class GraphMaker
{

    public:
        GraphMaker( std::string input_filename, int bincout );
        ~GraphMaker();

        void createGraphs();
    
    private:
        void parseData();
        void graphData();
        void analyzeData();
        void writeGraphData();

        void axis_scale( double min,double max,  double& y_ticks, double& y_m_ticks, double& y_scale_min, double& y_scale_max );



        DataSet data_set;

        std::string input_filename;
        /*! \brief set output_filename = input_filename + <data type> + jpg" */
        std::string output_filename;

        int bin_count;

        std::vector< std::string > graphOutputFiles;

};

#endif   /* ----- #ifndef GRAPH_MAKER_H  ----- */

#endif
