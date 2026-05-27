/* $Id$ */
#include "stdafx.h"

#ifdef ES

#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm> 
#include <iterator>
#include <cmath>
#include <math.h>

#include "dprintf.h"
#include "data_set.h"
#include "parse_data.h"
#include "graph_maker.h"

#include "gd.h"
#include "gdfontt.h"
#include "gdfonts.h"
#include "gdfontmb.h"
#include "gdfontl.h"
#include "gdfontg.h"

static void draw_text( gdImagePtr image, const char* text, int size, int x, int y , double angle = 0.0 );

/**
  @brief 

  @param input_file
  @param bincount
*/

GraphMaker::GraphMaker( std::string input_file, int bincount )
{
    input_filename = input_file;
    bin_count = bincount;

    /* make graphOutputFiles large enough */
    graphOutputFiles.resize( TOTAL_SIZE );

    /* graphOutputFiles */
    std::string file;

    file = output_filename + "dSOC" + output_filename_ext;
    graphOutputFiles[ dSOC ] = file;

    file = output_filename + "CH4" + output_filename_ext;
    graphOutputFiles[ CH4 ] = file;

    file = output_filename + "N2O" + output_filename_ext;
    graphOutputFiles[ N2O ] = file;

    file = output_filename + "NO" + output_filename_ext;
    graphOutputFiles[ NO ] = file;

    file = output_filename + "N2" + output_filename_ext;
    graphOutputFiles[ N2 ] = file;

    file = output_filename + "NH3" + output_filename_ext;
    graphOutputFiles[ NH3 ] = file;

    file = output_filename + "N_leaching" + output_filename_ext;
    graphOutputFiles[ N_leaching ] = file;

}

GraphMaker::~GraphMaker()
{
    /* close the files */
    //for_each( graphOutputFiles.begin(), graphOutputFiles.end(), fclose );

    /* destroy the images in memory */
    //for_each( gdImages.begin(), gdImages.end(), gdImageDestroy );
}
/*!
  \brief

  This function gets the data, parses it, performs the frequncy analysis on it,
  graphs the data and writes it to disk.

  \return void 
*/
void GraphMaker::createGraphs()
{
    parseData();
    analyzeData();
    graphData();
}

/*!
  \brief
    Reads data from \var input_filename and stores in in \var dataset

  \return void 
*/
void GraphMaker::parseData()
{
    ParseData pd( input_filename );
    pd.parse_data( data_set );
}

/*!
  \brief analyzeDataa() takes the data from parseData and 
        determines the left/right and count values using bin_count
  \return void 
*/
void GraphMaker::analyzeData()
{

    int count;
    double left;
    double right;

    for ( ElkhornDataSet::iterator it = data_set.data_set.begin(); it != data_set.data_set.end(); ++it )
    {
        sort( it->parse_data.begin(), it->parse_data.end() );

		//copy( it->parse_data.begin(), it->parse_data.end(), std::ostream_iterator< double >( std::cout, " " ) );
		//std::cout << "\n";

        double data_min = *( it->parse_data.begin() ); 
		double data_max;
        data_max = *( ( it->parse_data.end())-1 );

        double data_range = data_max - data_min;
        double bin_size = data_range / bin_count;

        vdebug( it->parse_data.size() );
        vdebug( data_min );
        vdebug( data_max );
        vdebug( bin_size );

        left = data_min;
        right = data_min+bin_size;
        count = 0;

        DataList l;
        double value;
        for ( DataList::iterator parse_data_it = it->parse_data.begin(); 
            parse_data_it != it->parse_data.end();
            ++parse_data_it )
        {
            //vdebug( data_size );

			value = *parse_data_it;
            //vdebug( left );
            //vdebug( value );
            //vdebug( right );

            if ( value < data_min )
                continue ; 

            if ( ( value >= left && value < right ) ||
                ( value >= data_max ) )
            {
                l.push_back( value );
            }
            else
            {

                count = l.size();
                ElkhornBinData bd( count, left, right );
                bd.list = l;

                it->bin_data_list.push_back( bd );
                left = right;
                right = right + bin_size;

                l.clear();

                if ( value >= data_max )
                {
                    l.push_back( value );
                }
                else
                {
                    --parse_data_it ;
                }
            }
        }

        if ( left < data_max )
        {
                count = l.size();
                ElkhornBinData bd( count, left, right );
                bd.list = l;

                it->bin_data_list.push_back( bd );
                l.clear();
        }

        vdebug( it->bin_data_list.size() );
        //copy( it->bin_data_list.begin(), it->bin_data_list.end(), std::ostream_iterator< ElkhornBinData >( std::cerr, "\n" ) );
    }
}

void draw_text( gdImagePtr image, const char* text, int size, int x, int y, double angle )
{
        int brect[8] = {0,0,0,0,0,0,0,0};

        /* draw x-axis title */
        char* err = gdImageStringFT( NULL, 
        &brect[0], 0, 
        "./arial.ttf", 
        size,  /* size */
        angle,  /* angle */
        0,
        0,
        const_cast< char*> ( text ) );

        if ( err )
            fprintf( stderr, "draw_text() error: %s\n", err );

        int black = gdImageColorAllocate( image, 0,0,0 );

        /* draw text */
        err = gdImageStringFT( image, 
            &brect[0], 
            black, 
            "./arial.ttf", 
            size,  /* size */
            angle,  /* angle */
            x,	
            y,
            const_cast< char* > ( text) );

        if ( err )
            fprintf( stderr, "draw_text() error: %s\n", err );

}

/*!
  \brief

  \param void

  \return void 
*/
void GraphMaker::graphData()
{
	
    for ( ElkhornDataSet::iterator it = data_set.data_set.begin(); it != data_set.data_set.end(); ++it )
    {
        double min = *( it->parse_data.begin() ); 
        double max = *( ( it->parse_data.end()) - 1); 

        ElkhornBinDataList bin_data = it->bin_data_list;
        ElkhornDataType data_type = it->data_set_type;
        std::string data_title = it->data_set_title;

        FILE* image_file;
        gdImagePtr image;

        image_file = fopen( graphOutputFiles[data_type].c_str(), "wb" );


        image = gdImageCreate( width, height );
        /* this sets the background color, in this case, white */
        gdImageColorAllocate( image, 255,255,255 );

        int black = gdImageColorAllocate( image, 0,0,0 );
        int blue = gdImageColorAllocate( image, 0,0,255 );


        double x0 = width*80/480;
        double y0 = height*320/360- 16;
        double dx = width*330/440;
        double dy = height*280/360;

        double x_range = static_cast< double > ( bin_data.size() );
        double x_ticks = x_range;
        double dx_c = dx / x_ticks;


		
        double min_y = 0;

        /* find max_y */
        int max_count = 0;
		ElkhornBinDataList::iterator bdit;

        for ( bdit = bin_data.begin(); bdit != bin_data.end(); ++bdit )
        {
            ElkhornBinData b = *bdit;
            if ( b.count > max_count )
                max_count = b.count;
        }
		
		/* add a little to max_count */
		max_count += ( max_count / 4 );

		min = 0;
		max = max_count;
        double y_ticks,y_m_ticks, y_scale_min, y_scale_max;
        axis_scale( min, max,  y_ticks, y_m_ticks, y_scale_min, y_scale_max );


        /* max_y is ElkhornBinData with the largest count */
        double max_y = static_cast< double >( max_count );
        
        double y_range = max_y - min_y;

        bool tight = ( dx_c < 10 ) ? true : false;

        unsigned int i = 0;

        /* draw bars of histogram */
        for ( bdit = bin_data.begin(); bdit != bin_data.end(); ++bdit )
        {
            ElkhornBinData b = *bdit;
            //vdebug( b );

            int count = b.count;
            double right;

            if ( (bdit+1) == bin_data.end() )
                right = bdit->right;
            else
                right = (bdit)->right;

            double x_pos0 = x0 + dx_c * i + ( tight ? 0 : 3 );
            double x_pos1 = x_pos0 + dx_c - ( tight ? 0 : 6 );

            double y_pos = y0 - dy * ( count - y_scale_min) / y_range;

            gdImageFilledRectangle( image, 
              static_cast< int > ( x_pos0 ), 
              static_cast< int > ( y_pos ), 
              static_cast< int > ( x_pos1 ), 
              static_cast< int > ( y0 ), 
              blue );
            gdImageRectangle( image, 
              static_cast< int > ( x_pos0 ), 
              static_cast< int > ( y_pos ), 
              static_cast< int > ( x_pos1 ), 
              static_cast< int > ( y0 ),
              black );
            i++;
        }
        gdImageRectangle( image, 
            static_cast< int > ( x0 ), 
            static_cast< int > ( y0-dy ), 
            static_cast< int > ( x0+dx ),
            static_cast< int > ( y0 ), 
            black
          );

		/* draw x-ticks labels */
		if ( bin_data.size() > 1 )
		{

			for ( i = 0; i < ( bin_data.size() +1 ); ++i )
			{
				std::ostringstream label;
					
				double value;

				if ( i == 0 || (i) != bin_data.size() )
				{
					
					ElkhornBinData bd = bin_data[i];

					value = bd.left;
				}
				else
				{
					ElkhornBinData bd = bin_data[i-1];
					value = bd.right;
				}
								
				if ( value > 10 ) 
				{
					int v = static_cast< int >( value );
					label << v;
				}
				else
				{
					label.precision( 2 );
					label << value;
				}

				double x_pos = x0 + dx_c * i;
				double t_len = 8;

				gdImageLine( image, 
					static_cast< int > ( x_pos ), 
					static_cast< int > ( y0 + t_len / 2 ), 
					static_cast< int > ( x_pos ), 
					static_cast< int > ( y0 ), 
					black );
				gdImageLine( image, 
					static_cast< int > ( x_pos ), 
					static_cast< int > ( y0-dy ), 
					static_cast< int > ( x_pos ), 
					static_cast< int > ( y0-dy+t_len ),
					black );

                int font_size = 10;
				/* draw x-axis ticks labels */
                draw_text( image, label.str().c_str(), font_size, 
                  static_cast<int>( x_pos-2 ), 
                  static_cast<int>( y0+label.str().length() + 14 ) );
			}
		}

			/* draw x-axis title */
			std::string x_title = data_title;

            draw_text( image, data_title.c_str(), 12,
                static_cast< int > ( x0+dx/2-4*x_title.length() ),
                static_cast< int > ( y0+34 ) );

            /* draw y-axis title */
            std::string y_title = "Count";

            draw_text( image, y_title.c_str(), 12,
            static_cast< int > ( x0-30 ),
            static_cast< int > ( y0-dy/2+3*y_title.length() ), -90/8 );

			for ( i = 0; i < y_ticks*y_m_ticks; i++ )
			{
            
				double y_pos = y0-dy/y_ticks/y_m_ticks*i;
				double t_len;
				if ( i % static_cast< int > ( y_m_ticks ) > 0 )
					t_len = 4;
				else
					t_len = 8;

				gdImageLine( image, 
					static_cast< int > ( x0 ),
					static_cast< int > ( y_pos ),
					static_cast< int > ( x0+t_len ), 
					static_cast< int > ( y_pos ),
					black );
        }

        /* draw y-labels */
        for ( int j = 0; j < max_count; j++ )
        {
            std::ostringstream label;
			label << j;
			
            double y_pos = y0-dy/y_ticks*j;
            double x_pos = x0-7*(1+label.str().length() );

            draw_text( image, label.str().c_str(), 10,
            static_cast< int > ( x_pos ),
            static_cast< int > ( y_pos + 8 ) );
        }

        /* create jpeg image */
        gdImageJpeg( image, image_file, -1 );

        /* close file */
        fclose( image_file );

        /* destroy image */
        gdImageDestroy( image );

    }
}
/**
  @brief 

  @param min
  @param max
  @param y_ticks
  @param y_m_ticks
  @param y_scale_min
  @param y_scale_max
*/

void GraphMaker::axis_scale( double min,double max,  double& y_ticks, double& y_m_ticks, double& y_scale_min, double& y_scale_max )
{
    double min_y = min;
    double max_y = max;
    double scale = 1;
    y_scale_min = 0;
    y_scale_max = 1;
    double y_range = 1;

    /* find y-scale */
    if ( max_y - min_y > 0 )
    {
        double b = 10;
        double e = log10( max_y - min_y );
        scale = pow( b, e );

        y_scale_min = scale*floor( min_y / scale );
        y_scale_max = scale*ceil( max_y / scale );
        y_range = ( y_scale_max - y_scale_min );

        if ( y_range >= 9*scale )
        {
            scale *= 10;
            y_scale_min = scale*floor(min_y / scale);
            y_scale_max = scale*ceil( max_y / scale );
        }

        while ( (scale > 1) && ( ( min_y > y_scale_min + y_range*0.2 ) || ( max_y < y_scale_max-y_range*0.2 ) ) )
        {
            scale /= 2;
            y_scale_min = scale*floor( min_y / scale );
            y_scale_max = ceil( max_y / scale );
        }
    }

    y_ticks = y_range;
    vdebug( y_ticks );

    while ( y_ticks >= 10 )
    {
        vdebug( y_ticks );
        y_ticks /= 10;
    }

    y_ticks = (y_ticks<2)?5:(y_ticks==2)?4:(y_ticks==3)?
	( (y_range/3)<(y_range/6)?3:6 ):(y_ticks==8)?4:y_ticks;

    //Find minor ticks
    double delta = y_range/y_ticks;

    y_m_ticks = ( delta / 4 <= delta / 5 ) ? 4 : 5;
}

#endif
