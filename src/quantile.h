//------------------------------------------------------------------------------
//  by Greg Ridgeway  Copyright (C) 2003
//  File:       quantile.h
//
//  License:    GNU GPL (version 2 or later)
//
//  Contents:   laplace object
//            
//  Owner:      gregr@rand.org
//
//  History:    10/8/2006   Created by Brian Kriegler (bk@stat.ucla.edu)
//              6/11/2007   gregr merged with official erboost 
//        
//------------------------------------------------------------------------------

#ifndef QUANTILE_H
#define QUANTILE_H

#include <algorithm>
#include "distribution.h"


class CQuantile: public CDistribution
{

public:

    CQuantile(double dAlpha);

    virtual ~CQuantile();

    erboostRESULT ComputeWorkingResponse(double *adY,
                                   double *adMisc,
                                   double *adOffset,
                                   double *adF, 
                                   double *adZ, 
                                   double *adWeight,
                                   bool *afInBag,
                                   unsigned long nTrain);

    erboostRESULT InitF(double *adY, 
                    double *adMisc,
                    double *adOffset,
                    double *adWeight,
                    double &dInitF, 
                    unsigned long cLength);

    erboostRESULT FitBestConstant(double *adY,
                              double *adMisc,
                              double *adOffset,
                              double *adW,
                              double *adF,
                              double *adZ,
                              unsigned long *aiNodeAssign,
                              unsigned long nTrain,
                              VEC_P_NODETERMINAL vecpTermNodes,
                              unsigned long cTermNodes,
                              unsigned long cMinObsInNode,
                              bool *afInBag,
                              double *adFadj);

    double Deviance(double *adY,
                    double *adMisc,
                    double *adOffset,
                    double *adWeight,
                    double *adF,
                    unsigned long cLength);

    double BagImprovement(double *adY,
                          double *adMisc,
                          double *adOffset,
                          double *adWeight,
                          double *adF,
                          double *adFadj,
                          bool *afInBag,
                          double dStepSize,
                          unsigned long nTrain);

private:
    vector<double> vecd;
    double dAlpha;
};

#endif // QUANTILE_H



