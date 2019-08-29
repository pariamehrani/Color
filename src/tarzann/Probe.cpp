#include<iostream>
#include <tarzann/Probe.h>
using namespace std;
using namespace tarzann;

//int main () {
//  ofstream myfile;
//  myfile.open ("./example.txt");
//  myfile << "Writing this to a file.\n";
//  myfile.close();
//  return 0;
//}



//probe constructor for all sheets and cells in a given layer
Probe::Probe(PLattice* lattice,string layer_name, uint32_t max_time)
{


    m_out_file.open("../../data"+layer_name+"_taskRslts.txt");


    m_max_time=max_time;
    m_lattice=lattice;
    m_local_layer=m_lattice->getLayer(layer_name);

    if(m_local_layer->getType() == TOP_LAYER)
        m_out_file.open("../../data"+layer_name+"_0_0_TopWinner.txt");


}

//probe constructor for all cells in a given sheet
Probe::Probe(PLattice* lattice,string layer_name,
             string sheet_name, uint32_t max_time)
{
    m_out_file.open ("../../data/"+layer_name+"_"
                     +sheet_name+"_taskRslts.txt");


    m_max_time=max_time;
    m_lattice=lattice;
    m_local_layer=m_lattice->getLayer(layer_name);
    m_local_sheet=m_lattice->getLayer(layer_name)->getSheet(sheet_name);

    if(m_local_layer->getType() == TOP_LAYER)
    m_out_top_winner.open ("../../data/"+layer_name
                            +"_"+sheet_name+"_TopWinner.txt");
}

//probe constructor for single cells in a given sheet and layer
Probe::Probe(PLattice* lattice,string layer_name,
             string sheet_name,
             vector<Nrn> &coords,
             uint32_t max_time)
{
    m_out_file.open ("../../../data/SingleNrs_in_"+layer_name+"_"+
                     sheet_name+"_taskRslts.txt");


    m_max_time=max_time;
    m_lattice=lattice;
    m_local_layer=m_lattice->getLayer(layer_name);
    m_local_sheet=m_local_layer->getSheet(sheet_name);
    m_nrn=coords;

    if(m_local_layer->getType() == TOP_LAYER)
    m_out_top_winner.open ("../../../data/"+layer_name
                            +"_"+sheet_name+"_TopWinner.txt");
}




void Probe::updateNeuronsRec(uint32_t time_){
    uint32_t w,h;
    m_max_idx=m_nrn.size()-1;
    Matrix* actty=m_local_sheet->getOutput();
    Matrix* frInput=m_local_sheet->getConvolvedInputs();
    Array2D<H_curr>* h_curr= m_local_sheet->getH_currs();


    if(time_==0)m_out_file<<"sgl_cells=[";
    for(int i=0;i<=m_max_idx;i++){

        w=m_nrn[i].x,    h=m_nrn[i].y;
       float ih_s=(*h_curr)(w,h).h_slow;
       float ih_f=(*h_curr)(w,h).h_fast;

        m_out_file << w<<" "<<h<<" "<<time_
                   <<" "<<ih_f<<" "<<ih_s<<" "
                   <<" "<<(*actty)(w,h)<<" "
                   <<(*frInput)(w,h)<<"\n";
    }
    if(time_==m_max_time){
        m_out_file<<"];"<<endl;
        m_out_file .close();
    }
}

void Probe::updateSheetRec(uint32_t time_){

    Matrix* actty=m_local_sheet->getOutput();


    Array2D<H_curr>* h_curr= m_local_sheet->getH_currs();


    m_w_max=actty->getXSize()-1;
    m_h_max=actty->getYSize()-1;

    for(uint32_t w=0;w<=m_w_max;w++){
        for(uint32_t h=0;h<=m_h_max;h++){
            float ih_s,ih_f;
            ih_s=(*h_curr)(w,h).h_slow;
            ih_f=(*h_curr)(w,h).h_fast;

            m_out_file << time_<<" "<<w<<" "<<h<<" "<<(*actty)(w,h)<<"\n";
        }
    }
    if(time_==m_max_time)m_out_file .close();

}

void Probe::updateLayerRec(uint32_t time_){

    Sheet* the_sheet;
    Matrix* actty;
    Array2D<H_curr>* h_curr;
    std::vector<Sheet*> sheet_vect;
    m_local_layer->getSheets(sheet_vect);
    string sheet_name;
    int max=sheet_vect.size()-1;

    for(int sheet_idx=0;sheet_idx<=max;sheet_idx++){

      the_sheet=(Sheet*)sheet_vect[sheet_idx];
      sheet_name=the_sheet->getName();

      m_out_file << sheet_name<<endl;

      actty=the_sheet->getOutput();
      h_curr= the_sheet->getH_currs();
      m_w_max=actty->getXSize()-1;
      m_h_max=actty->getYSize()-1;


      for(uint32_t w=0;w<=m_w_max;w++){
          for(uint32_t h=0;h<=m_h_max;h++){

              float ih_s,ih_f;
              ih_s=(*h_curr)(w,h).h_slow;
              ih_f=(*h_curr)(w,h).h_fast;

              m_out_file <<sheet_name<<"  "<< time_
                         <<" "<<w<<" "<<h
                         <<" "<<(*actty)(w,h)<<"\n";

              if(w==m_w_max)m_out_file <<"\n"<<endl;
          }
      }

    }
    if(time_==m_max_time)m_out_file .close();
}


void Probe::PrintWinnersInSheet(string sheet_name,
                               uint32_t time_,
                               float threshold){

    float nrn_actty=0;
    //string
    m_actty=m_local_sheet->getOutput();
    m_w_max=m_actty->getXSize();
    m_h_max=m_actty->getYSize();


    if(time_==0)m_Winnersoutptfile.open(sheet_name+"Winners.txt");

    for(uint32_t w=0;w<m_w_max;w++){
        for(uint32_t h=0;h<m_h_max;h++){
            nrn_actty=(*m_actty)(w,h);
            if(nrn_actty>=threshold)
            m_Winnersoutptfile
                    <<time_<<" "<<w<<" "<<h<<" "<<nrn_actty<<"\n";
        }
    }
    if(time_==m_max_time)m_Winnersoutptfile.close();

}

void Probe::printOverallWinner(uint32_t time){

    if(time==0)m_out_top_winner<<"TopWinner=[";
    if(time==m_max_time)m_out_top_winner<<"]";

    m_out_top_winner<<time<<" "<<getGlobalWinner().x<<" "
                    <<getGlobalWinner().y<<" "
                    <<getGlobalWinner().z<<" "<<endl;
}

Winner Probe::getGlobalWinner(){

    Winner Nwk_winner;
    Sheet* the_sheet;
    Layer* the_layer;
    vector<Sheet*> sheet_vect;
    vector<Layer*> layer_vect;

    m_lattice->getLayers(layer_vect);

    int max_lyr_idx=layer_vect.size()-1;

    for(int layer_idx=0;layer_idx<=max_lyr_idx;layer_idx++){

        sheet_vect.clear();

        the_layer = (Layer*)layer_vect[layer_idx];

        the_layer->getSheets(sheet_vect);

        int max_sheet_idx=sheet_vect.size();

        if(the_layer->getType() == TOP_LAYER && max_sheet_idx==1)
        {
            the_sheet=(Sheet*)sheet_vect[max_sheet_idx-1];

            Nwk_winner=the_sheet->getOutput()->getMaxActivation();
            //cout<<Nwk_winner.x<<" "<<Nwk_winner.y<<" "<<Nwk_winner.z<<" "<<endl;

        }
        else{
//            cout<<"the top layer has more than one "
//                  "sheet or isn't active"<<endl;
//            cout<<"the function returns "
//                  "x=0, y=0, activation=0"<<endl;

            Nwk_winner.x=0,Nwk_winner.y=0,Nwk_winner.z=0;
        }
    }

    return Nwk_winner;


}


void Probe::UpdateWinnersInLattice(uint32_t time_){

    Layer* the_layer;
    Sheet* the_sheet;
    Matrix* actty;
    std::vector<Layer*> layer_vect;
    std::vector<Sheet*> sheet_vect;
    m_lattice->getLayers(layer_vect);
    string layer_name,sheet_name;

    int max_lyr_idx=layer_vect.size()-1;

    for(int layer_idx=0;layer_idx<=max_lyr_idx;layer_idx++){

        sheet_vect.clear();
        the_layer = (Layer*)layer_vect[layer_idx];
        the_layer->getSheets(sheet_vect);
        layer_name = the_layer->getName();
        int max_sheet_idx=sheet_vect.size()-1;

        m_out_file << layer_name<<endl;

        for(int sheet_idx=0;sheet_idx<=max_sheet_idx;sheet_idx++){

            the_sheet=(Sheet*)sheet_vect[sheet_idx];
            sheet_name=the_sheet->getName();
            actty=the_sheet->getOutput();
            m_w_max=actty->getXSize()-1;
            m_h_max=actty->getYSize()-1;

            m_out_file << sheet_name<<endl;

            for(uint32_t w=0;w<=m_w_max;w++){
                for(uint32_t h=0;h<=m_h_max;h++){
                    m_out_file <<layer_name<<"  "<<sheet_name
                                           <<"  "<< time_
                                           <<" "<<w<<" "<<h<<" "
                                           <<(*actty)(w,h)<<"\n";

                    if(w==m_w_max)m_out_file <<"\n"<<endl;
                }
            }
        }


    }


}

void Probe::displaySheetRslt(Matrix* matrix){

    cv::Mat img4 = cv::Mat(matrix->getYSize(),
                           matrix->getXSize(),
                           CV_32F,
                           matrix->getData(),
                           matrix->getStep());

    cv::Mat display4 = img4.clone();

    cv::normalize(img4,display4,0,255,cv::NORM_MINMAX);
    display4.convertTo(display4,8U);
    cv::imshow("Display",display4);
    cv::waitKey(10);

}


Probe::~Probe()
{

}








