#define CATCH_CONFIG_MAIN

#include <iostream>
#include <limits.h>
#include <sys/stat.h>
#include <vector>

#include "cs221util/RGBAPixel.h"
#include "cs221util/PNG.h"
#include "cs221util/catch.hpp"

#include "decoder.h"
#include "treasureMap.h"

using namespace std;
using namespace cs221util;


#define IMAGEDIR "images/"
#define SOLNIMGDIR "soln_images/"

/**
 * Test Cases
 * these are just examples of a logical flow similar to 
 * that of main.cpp. We suggest decoupling the embedding
 * tests from the decoding tests, but we leave it to you
 * to do so.
 */

TEST_CASE("treasureMap::basic no cycles", "[weight=1][part=treasureMap]")
{

	PNG maze;
	maze.readFromFile("images/snake.png");
	pair<int,int> start(1,1);

    PNG base;
    base.readFromFile("images/sunshine.png");

    treasureMap M(base, maze, start);
    cout << "Made it to line 41" << endl;

    PNG treasure = M.renderMap();
    cout << "Made it to line 44" << endl;
	treasure.writeToFile("images/embeddedsnake00.png");
    PNG treasureans;
    treasureans.readFromFile("images/embeddedsnake.png");
    REQUIRE( treasure == treasureans );
    cout << "Made it to line 49" << endl;

    PNG treasuremaze = M.renderMaze();
    cout << "Made it to line 52" << endl;
	treasuremaze.writeToFile("images/greyedsnake00.png");
    PNG treasuremazeans;
	treasuremazeans.readFromFile("images/greyedsnake.png");
    REQUIRE( treasuremaze == treasuremazeans );
    cout << "Reached line 57" << endl;

    decoder dec(treasure,start);

    cout << "Reached line 61" << endl;

    PNG soln = dec.renderSolution();
    cout << "Reached line 64" << endl;
    soln.writeToFile("images/solnsnake00.png");
    PNG solnans;
    solnans.readFromFile("images/solnsnake.png");
    REQUIRE( soln == solnans );
    cout << "Reached line 69" << endl;

    ///////////////////////////////////////

    PNG solnmaze = dec.renderMaze();
    solnmaze.writeToFile("images/solnsnakemaze00.png");
    PNG solnmazeans;
    solnmazeans.readFromFile("images/solnsnakemaze.png");
    REQUIRE( solnmaze == solnmazeans );

}

TEST_CASE("decoder::basic cycles", "[weight=1][part=decoder]")
{
	PNG maze;
	maze.readFromFile("images/maze.png");
	pair<int,int> start(1,1);

    PNG base;
    base.readFromFile("images/sunshine.png");

    treasureMap M(base, maze, start);

    PNG treasure = M.renderMap();
	treasure.writeToFile("images/embeddedmaze00.png");
    PNG treasureans;
    treasureans.readFromFile("images/embeddedmaze.png");
    REQUIRE( treasure == treasureans );
    cout << "Reached line 91" << endl;

    PNG treasuremaze = M.renderMaze();
	treasuremaze.writeToFile("images/greyedmaze00.png");
    PNG treasuremazeans;
	treasuremazeans.readFromFile("images/greyedmaze.png");
    REQUIRE( treasuremaze == treasuremazeans );
    cout << "Reached line 101" << endl;

    decoder dec(treasure,start);
    cout << "Reached line 104" << endl;

    PNG soln = dec.renderSolution();
    soln.writeToFile("images/solnmaze00.png");
    PNG solnans;
    solnans.readFromFile("images/solnmaze.png");
    REQUIRE( soln == solnans );
    cout << "Reached line 114" << endl;

    PNG solnmaze = dec.renderMaze();
    solnmaze.writeToFile("images/solnmazemaze00.png");
    PNG solnmazeans;
    solnmazeans.readFromFile("images/solnmazemaze.png");
    REQUIRE( solnmaze == solnmazeans );

}

