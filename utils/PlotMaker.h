//
// Created by Bartek on 2023-01-15.
//

#ifndef SANDBOX_PLOTMAKER_H
#define SANDBOX_PLOTMAKER_H
#include <iostream>
#include <vector>
#include "DataReader.h"
#include "pbPlots/pbPlots.hpp"
#include "pbPlots/supportLib.hpp"
#include "../physics/Physics.h"


class PlotMaker {
public:

    static std::vector<double> xPlanet;
    static std::vector<double> yPlanet;
    static constexpr int NUMBER_OF_PLANET_POINTS = 64;

    static void plot(std::vector<double>& x1, std::vector<double>& y1, std::vector<double>& x2, std::vector<double>& y2, const std::string& outputFileName) {
        RGBABitmapImageReference* imageRef = CreateRGBABitmapImageReference();


        ScatterPlotSeries *series = GetDefaultScatterPlotSeriesSettings();
        series->xs = &x1;
        series->ys = &y1;
        series->linearInterpolation = true;
        series->lineType = toVector(L"solid");
        series->lineThickness = 2;
        series->color = CreateRGBColor(0, 1, 0);

        ScatterPlotSeries *series2 = GetDefaultScatterPlotSeriesSettings();
        series2->xs = &x2;
        series2->ys = &y2;
        series2->linearInterpolation = true;
        series2->lineType = toVector(L"solid");
        series2->lineThickness = 2;
        series2->color = CreateRGBColor(0, 0, 1);

        ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();
        settings->width = 600;
        settings->height = 400;
        settings->autoBoundaries = true;
        settings->autoPadding = true;
        settings->title = toVector(L"");
        settings->xLabel = toVector(L"");
        settings->yLabel = toVector(L"");
        settings->scatterPlotSeries->push_back(series);
        settings->scatterPlotSeries->push_back(series2);

        auto *errorMessage = (StringReference *) "error;(";
        DrawScatterPlotFromSettings(imageRef, settings, errorMessage);

        std::vector<double> *pngData = ConvertToPNG(imageRef->image);

        WriteToFile(pngData, outputFileName);

        DeleteImage(imageRef->image);
    }

    static void plotRocketTrajectoryToFiles() {
//        constexpr double angleDeltaVal = (2*Physics::PI / (NUMBER_OF_PLANET_POINTS-1));
//        SetPlanetXValues<NUMBER_OF_PLANET_POINTS, angleDeltaVal, Physics::EARTH_RADIUS>(xPlanet);
//        SetPlanetYValues<NUMBER_OF_PLANET_POINTS, angleDeltaVal, Physics::EARTH_RADIUS>(yPlanet);

        std::vector<std::string> data = DataReader::readFile("rocketTelemetry_live.txt");
        std::vector<double> x = DataReader::getValuesByColumn(data, 1);
        std::vector<double> yRocket = DataReader::getValuesByColumn(data, 2);
        std::vector<double> yEarth = DataReader::getValuesByColumn(data, 3);

        PlotMaker::plot(x, yEarth, x, yRocket, "rocketTrajectory.png");
        PlotMaker::plot(xPlanet, yPlanet, x, yRocket,  "rocketTrajectoryFull.png");
    }

private:
    static constexpr double angleDelta(int numberOfPoints) {
        return (2*Physics::PI / (numberOfPoints-1));
    }

    template<int N, double angleDelta, double planetRadius, typename T>
    static constexpr void SetPlanetXValues(T& values) {
        if constexpr (N > 0) {
            values[N-1] = planetRadius * sin(angleDelta * (N-1));
            SetPlanetXValues<N-1, angleDelta, planetRadius>(values);
        }
    }

    template<int N, double angleDelta, double planetRadius, typename T>
    static constexpr void SetPlanetYValues(T& values) {
        if constexpr (N > 0) {
            values[N-1] = planetRadius * cos(angleDelta * (N-1));
            SetPlanetYValues<N-1, angleDelta, planetRadius>(values);
        }
    }
};

//std::vector<double> PlotMaker::xPlanet = std::vector<double>(NUMBER_OF_PLANET_POINTS);
//std::vector<double> PlotMaker::yPlanet = std::vector<double>(NUMBER_OF_PLANET_POINTS);


std::vector<double> PlotMaker::xPlanet = {0,
                                                  635.938864,
                                                  1265.523637,
                                                  1882.463716,
                                                  2480.594841,
                                                  3053.940681,
                                                  3596.772556,
                                                  4103.666668,
                                                  4569.558299,
                                                  4989.792414,
                                                  5360.170173,
                                                  5676.990884,
                                                  5937.088978,
                                                  6137.865641,
                                                  6277.31478,
                                                  6354.043065,
                                                  6367.283851,
                                                  6316.904843,
                                                  6203.409409,
                                                  6027.931559,
                                                  5792.224609,
                                                  5498.643666,
                                                  5150.122092,
                                                  4750.142202,
                                                  4302.70046,
                                                  3812.267558,
                                                  3283.743739,
                                                  2722.409837,
                                                  2133.874516,
                                                  1524.018227,
                                                  898.9344513,
                                                  264.8688197,
                                                  -371.8432936,
                                                  -1004.840072,
                                                  -1627.79682,
                                                  -2234.48916,
                                                  -2818.855224,
                                                  -3375.056218,
                                                  -3897.534765,
                                                  -4381.070434,
                                                  -4820.831895,
                                                  -5212.425197,
                                                  -5551.93767,
                                                  -5835.977017,
                                                  -6061.705211,
                                                  -6226.86685,
                                                  -6329.811693,
                                                  -6369.511151,
                                                  -6345.568558,
                                                  -6258.223142,
                                                  -6108.34763,
                                                  -5897.439526,
                                                  -5627.606157,
                                                  -5301.543607,
                                                  -4922.509786,
                                                  -4494.291874,
                                                  -4021.168483,
                                                  -3507.866906,
                                                  -2959.515883,
                                                  -2381.594355,
                                                  -1779.876724,
                                                  -1160.375152,
                                                  -529.2794959,
                                                  107.1045461
};

std::vector<double> PlotMaker::yPlanet = {
        6370,
        6338.176533,
        6243.024101,
        6085.493436,
        5867.158532,
        5590.200919,
        5257.387867,
        4872.044733,
        4438.021739,
        3959.655498,
        3441.725688,
        2889.407293,
        2308.218896,
        1703.967538,
        1082.6907,
        450.5959746,
        -186.0009571,
        -820.7394287,
        -1447.277343,
        -2059.354541,
        -2650.855349,
        -3215.869686,
        -3748.752117,
        -4244.178256,
        -4697.197968,
        -5103.284831,
        -5458.381359,
        -5758.939545,
        -6001.95631,
        -6185.003512,
        -6306.252203,
        -6364.490907,
        -6359.137722,
        -6290.246134,
        -6158.504487,
        -5965.229098,
        -5712.351112,
        -5402.397202,
        -5038.464325,
        -4624.188778,
        -4163.709865,
        -3661.628539,
        -3122.961432,
        -2553.090726,
        -1957.710382,
        -1342.769242,
        -714.4115966,
        -78.91578626,
        557.3685245,
        1188.083793,
        1806.928121,
        2407.718221,
        2984.451196,
        3531.364521,
        4042.99362,
        4514.226462,
        4940.354646,
        5317.120439,
        5640.759323,
        5908.037604,
        6116.284726,
        6263.419953,
        6347.973158,
        6369.099514
};

#endif //SANDBOX_PLOTMAKER_H
