class Event{
	private:
		ReadFile *rf;

                TH1* hbdc1tdc[8];
                TH1* hbdc2tdc[8];
                TH1* hfdc0tdc[8];
                TH1* hfdc2tdc[14];

                TH2* hBDC1TDC[8];
                TH2* hBDC2TDC[8];
                TH2* hFDC0TDC[8];
                TH2* hFDC2TDC[14];

                TH2* hBDC1Layer[4];
                TH2* hBDC2Layer[4];
                TH2* hFDC0Layer[4];
                TH2* hFDC2Layer[7];


	public:
		Event(){}
		Event(ReadFile *rf):rf(rf){
			createOutput();
		}
		void createOutput(){
			for (int ilayer=0;ilayer<8;++ilayer){
				hbdc1tdc[ilayer] = new TH1I(Form("hbdc1tdc%d",ilayer),
						Form("BDC1 TDC layer=%d",ilayer),200,1700,1900);
				hBDC1TDC[ilayer] = new TH2I(Form("hBDC1TDC%d",ilayer),
						Form("BDC1 TDC layer=%d",ilayer),200,1700,1900,16,-0.5,15.5);

			}


			for (int ilayer=0;ilayer<8;++ilayer){
				hbdc2tdc[ilayer] = new TH1I(Form("hbdc2tdc%d",ilayer),
						Form("BDC2 TDC layer=%d",ilayer),200,1700,1900);
				hBDC2TDC[ilayer] = new TH2I(Form("hBDC2TDC%d",ilayer),
						Form("BDC2 TDC layer=%d",ilayer),200,1700,1900,16,-0.5,15.5);
			}
			for (int ilayer=0;ilayer<8;++ilayer){
				hfdc0tdc[ilayer] = new TH1I(Form("hfdc0tdc%d",ilayer),
						Form("FDC0 TDC layer=%d",ilayer),300,1600,1900);
				hFDC0TDC[ilayer] = new TH2I(Form("hFDC0TDC%d",ilayer),
						Form("FDC0 TDC layer=%d",ilayer),300,1600,1900,32,-0.5,31.5);
			}
			for (int ilayer=0;ilayer<14;++ilayer){
				hfdc2tdc[ilayer] = new TH1I(Form("hfdc2tdc%d",ilayer),
						Form("FDC2 TDC layer=%d",ilayer),900,1000,1900);
				hFDC2TDC[ilayer] = new TH2I(Form("hFDC2TDC%d",ilayer),
						Form("FDC2 TDC layer=%d",ilayer),900,1000,1900,112,-0.5,111.5);
			}

		}
		~Event(){
		}
		bool selectEvent(){
			return rf->goodGate();
		}
		bool goodBDC1Gate(){
			return rf->goodBDC1Gate();
		}
		void fillBDC1(){
			fillTDC(hbdc1tdc,rf->getBDC1NHit(),rf->getBDC1LayerId(),rf->getBDC1TDC());
			fillTDCvsWire(hBDC1TDC,rf->getBDC1NHit(),rf->getBDC1LayerId(),rf->getBDC1WireId(),rf->getBDC1TDC());
		}
		bool goodBDC2Gate(){
			return rf->goodBDC2Gate();
		}
		void fillBDC2(){
			fillTDC(hbdc2tdc,rf->getBDC2NHit(),rf->getBDC2LayerId(),rf->getBDC2TDC());
			fillTDCvsWire(hBDC2TDC,rf->getBDC2NHit(),rf->getBDC2LayerId(),rf->getBDC2WireId(),rf->getBDC2TDC());
	
		}
		bool goodFDC0Gate(){
			return rf->goodFDC0Gate();
		}
		void fillFDC0(){
			fillTDC(hfdc0tdc,rf->getFDC0NHit(),rf->getFDC0LayerId(),rf->getFDC0TDC());
			fillTDCvsWire(hFDC0TDC,rf->getFDC0NHit(),rf->getFDC0LayerId(),rf->getFDC0WireId(),rf->getFDC0TDC());
	
		}
		bool goodFDC2Gate(){
			return rf->goodFDC2Gate();
		}
		void fillFDC2(){
		}

		void fillTDC(TH1* h[8],int nhits, vector<double> layerid, vector<double> TDC){
			for (int i=0;i<nhits;i++){
				int layer = layerid[i];
				h[layer]->Fill(TDC[i]);
			}

		}

		void fillTDCvsWire(TH2* h[8],int nhits, vector<double> layerid, vector<double> wireid, vector<double> TDC){
			for (int i=0;i<nhits;i++){
				int layer = layerid[i];
				h[layer]->Fill(TDC[i],wireid[i]);
			}

		}

		void setBranch(TTree *tree){
		}
		void write(){
			for (int ilayer=0;ilayer<8;++ilayer){
				hbdc1tdc[ilayer]->Write(); 
				hBDC1TDC[ilayer]->Write(); 

				hbdc2tdc[ilayer]->Write(); 
				hBDC2TDC[ilayer]->Write(); 

				hfdc0tdc[ilayer]->Write(); 
				hFDC0TDC[ilayer]->Write(); 

			}


		}
};
