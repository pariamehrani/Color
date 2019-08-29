/**
 * @brief   This class extracts the output from the temporal evolution
 *          of the units pixel by pixel depending on the used function
 * @author  Oscar J. Avella-Gonzalez
 * @date    May 27, 2016
 */


#ifndef Probe_H
#define Probe_H

#include <fstream>
#include<iostream>
#include<tarzann/PLattice.h>
#include<tarzann/NeuronST.h>

struct Nrn{
    uint32_t x;
    uint32_t y;
};

namespace tarzann {


class Probe{

    public:

    //probe to record whole Layer results
    Probe(PLattice* lattice,
                string layer_name,
                uint32_t max_time);


    //probe to record whole Sheet results
    Probe(PLattice* lattice,
                string layer_name,
                string sheet_name,
                uint32_t max_time);

    //probe to record individual single neuron results
    Probe(PLattice* lattice,
                string layer_name,
                string sheet_name,
                vector<Nrn> &coords,
                uint32_t max_time);





   void updateNeuronsRec(uint32_t time_);

   void updateSheetRec(uint32_t time_);

   void updateLayerRec(uint32_t time_);


   void PrintWinnersInSheet(string sheet_name,
                           uint32_t time_,
                           float threshold);

   void UpdateWinnersInLattice(uint32_t time_);

   void displaySheetRslt(Matrix* matrix);


   Winner getGlobalWinner();
   void printOverallWinner(uint32_t time);


   float cellsAboveThreshold();

    protected:
    std::ofstream m_out_file;
    std::ofstream m_out_top_winner;
    std::ofstream m_Winnersoutptfile;
    PLattice* m_lattice;
    Layer* m_local_layer;
    Sheet* m_local_sheet;
    vector<Nrn> m_nrn;
    uint32_t m_max_time;
    Matrix* m_actty;
    Array2D<H_curr>* m_h_currs;
    uint32_t m_max_idx,m_w_max,m_h_max;



    ~Probe();


};


}


#endif
