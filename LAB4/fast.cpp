/*
 * fast < input.txt
 *
 * Compute and plot all line segments involving 4 points in input.txt
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
#include <unordered_set>
#include "point.h"
#include "window.h"

using namespace std;

int main(int argc, const char *argv[])
{
    WindowPtr window = create_window(argc, argv);
    if (!window)
        return 1;

    // The array of points
    vector<Point> points;

    // Read tolerance from cin
    double tolerance{};
    cin >> tolerance;

    // Read points from cin
    int N{};
    cin >> N;

    for (int i{0}; i < N; ++i)
    {
        double x{}, y{};
        cin >> x >> y;
        points.push_back(Point{x, y});
    }

    // draw points to screen all at once
    window->draw_points(points);

    // Sort points by their natural order. Makes finding endpoints a bit easier.
    sort(points.begin(), points.end());

    auto begin = chrono::high_resolution_clock::now();

    /////////////////////////////////////////////////////////////////////////////
    // Draw any lines that you find in 'points' using the function 'window->draw_line'.
    /////////////////////////////////////////////////////////////////////////////

    // MIN LÖSNING (1) (funkar)
    vector<Point> tmp{points};
    int itres{};
    for (auto origo : points)
    {
        std::cout << itres++ << std::endl;

        PolarSorter ps{origo};
        sort(tmp.begin(), tmp.end(), ps);
        vector<Point> results{origo};
        for (int i{1}; i < N - 2; ++i)
        {
            if (i < N - 1 && origo.sameSlope(tmp[i], tmp[i + 1], tolerance))
            {
                results.push_back(tmp[i]);
            }
            else
            {
                if (results.size() > 2)
                {
                    window->draw_line(results);
                }
                results = {origo};
            }
        }
        if (results.size() > 2)
        {
            window->draw_line(results);
        }
    }
    //Min Lösning (2) (funkar snabbare på större tester (kanske kan ske hashkollisioner(inte stabil))använder inte någon sort)
    // int itres{1}; // räkna iterationer
    // for (auto origo : points)
    // {                                    
    //     std::cout << itres++ << std::endl;
    //     unordered_map<int, vector<Point>> slope_map; // skapa en map för att gruppera punkters slope relativivt till origo
    //     for (auto &point : points) //beräknar alla slopes och lägger in dem 
    //     {
    //         if (point.x == origo.x && point.y == origo.y)
    //             continue;                                        // skippar att lägga till origo
    //         int slope_key = static_cast<int>(origo.slopeTo(point) / tolerance); //grupperar slopes med tolerans, för att avrunda slopesen så görs den om till en int
    //         slope_map[slope_key].push_back(point);               // lägger till den i relevanta slope gruppen
    //     }
    //     for (auto &p_slope : slope_map) //hitta alla slopes som har 4 eller mer punkter och skriv ut dem
    //     {
    //         vector<Point> &p_vector = p_slope.second; // hämtar ut vectorn med points ut mapen
    //         if (p_vector.size() >= 3) // kollar om det finns tre st points i vectorn
    //         {
    //             p_vector.push_back(origo); // ta med origo
    //             window->draw_line(p_vector); // skriv ut linjen
    //         }
    //     }
    // }

    auto end = chrono::high_resolution_clock::now();
    cout << "Computing line segments took "
         << std::chrono::duration_cast<chrono::milliseconds>(end - begin).count()
         << " milliseconds." << endl;

    // wait for user to terminate program
    window->run();

    return 0;
}
