
class LoadCut
{
		private:


		public:
				LoadCut(){
				}
				~LoadCut(){
				}

				void loadHodBe10Be10(){
						gROOT->ProcessLine(".x rootfiles/cutBe10Bar24Be10.C");
						gROOT->ProcessLine(".x rootfiles/cutBe10Bar23Be10.C");
						gROOT->ProcessLine(".x rootfiles/cutBe10Bar22Be10.C");
						gROOT->ProcessLine(".x rootfiles/cutBe10Bar21Be10.C");
						gROOT->ProcessLine(".x rootfiles/cutBe10Bar20Be10.C");
						gROOT->ProcessLine(".x rootfiles/cutBe10Bar19Be10.C");
						gROOT->ProcessLine(".x rootfiles/cutBe10Bar18Be10.C");
						gROOT->ProcessLine(".x rootfiles/cutBe10Bar17Be10.C");
						gROOT->ProcessLine(".x rootfiles/cutBe10Bar16Be10.C");
						gROOT->ProcessLine(".x rootfiles/cutBe10Bar15Be10.C");
						gROOT->ProcessLine(".x rootfiles/cutBe10Bar14Be10.C");
						gROOT->ProcessLine(".x rootfiles/cutBe10Bar13Be10.C");
						gROOT->ProcessLine(".x rootfiles/cutBe10Bar12Be10.C");
						gROOT->ProcessLine(".x rootfiles/cutBe10Bar11Be10.C");
						gROOT->ProcessLine(".x rootfiles/cutBe10Bar10Be10.C");
						gROOT->ProcessLine(".x rootfiles/cutBe10Bar9Be10.C");
						gROOT->ProcessLine(".x rootfiles/cutBe10Bar8Be10.C");
						gROOT->ProcessLine(".x rootfiles/cutBe10Bar7Be10.C");

				}
				void loadHodBe10Be9(){
						gROOT->ProcessLine(".x rootfiles/cutBe10Bar23Be9.C");
						gROOT->ProcessLine(".x rootfiles/cutBe10Bar22Be9.C");
						gROOT->ProcessLine(".x rootfiles/cutBe10Bar21Be9.C");
						gROOT->ProcessLine(".x rootfiles/cutBe10Bar20Be9.C");
						gROOT->ProcessLine(".x rootfiles/cutBe10Bar19Be9.C");


				}
				void loadHodBe12Be12(){
						gROOT->ProcessLine(".x rootfiles/cutBe12Bar23Be12.C");
						gROOT->ProcessLine(".x rootfiles/cutBe12Bar22Be12.C");
						gROOT->ProcessLine(".x rootfiles/cutBe12Bar21Be12.C");
						gROOT->ProcessLine(".x rootfiles/cutBe12Bar20Be12.C");
						gROOT->ProcessLine(".x rootfiles/cutBe12Bar19Be12.C");


				}
				void loadHodBe14Be14BeamRegion(){
//						gROOT->ProcessLine(".x rootfiles/cutBe14Bar33Be14.C");
//						gROOT->ProcessLine(".x rootfiles/cutBe14Bar32Be14.C");
//						gROOT->ProcessLine(".x rootfiles/cutBe14Bar31Be14.C");
//						gROOT->ProcessLine(".x rootfiles/cutBe14Bar30Be14.C");
//						gROOT->ProcessLine(".x rootfiles/cutBe14Bar29Be14.C");
//						gROOT->ProcessLine(".x rootfiles/cutBe14Bar28Be14.C");
//						gROOT->ProcessLine(".x rootfiles/cutBe14Bar27Be14.C");
	
						gROOT->ProcessLine(".x rootfiles/cutBe14Bar33Be14.C");
						gROOT->ProcessLine(".x rootfiles/cutBe14Bar32Be14.C");
						gROOT->ProcessLine(".x rootfiles/cutBe14Bar31Be14.C");
						gROOT->ProcessLine(".x rootfiles/cutBe14Bar30Be14.C");
						gROOT->ProcessLine(".x rootfiles/cutBe14Bar29Be14.C");
						gROOT->ProcessLine(".x rootfiles/cutBe14Bar28Be14.C");
						gROOT->ProcessLine(".x rootfiles/cutBe14Bar27Be14.C");
				}
				void loadHodBe14Be14HODF(){

						gROOT->ProcessLine(".x rootfiles/cutBe14Bar23Be14.C");
						gROOT->ProcessLine(".x rootfiles/cutBe14Bar22Be14.C");
						gROOT->ProcessLine(".x rootfiles/cutBe14Bar21Be14.C");
						gROOT->ProcessLine(".x rootfiles/cutBe14Bar20Be14.C");
						gROOT->ProcessLine(".x rootfiles/cutBe14Bar19Be14.C");

				}


				void loadHodBe14Be14(){

						loadHodBe14Be14BeamRegion();
						loadHodBe14Be14HODF();
				}
				void loadHodBe14Be12(){
						gROOT->ProcessLine(".x rootfiles/cutBe14Bar27Be12.C");
						gROOT->ProcessLine(".x rootfiles/cutBe14Bar26Be12.C");
						gROOT->ProcessLine(".x rootfiles/cutBe14Bar25Be12.C");
						gROOT->ProcessLine(".x rootfiles/cutBe14Bar24Be12.C");
						gROOT->ProcessLine(".x rootfiles/cutBe14Bar23Be12.C");
						gROOT->ProcessLine(".x rootfiles/cutBe14Bar22Be12.C");
						gROOT->ProcessLine(".x rootfiles/cutBe14Bar21Be12.C");
						gROOT->ProcessLine(".x rootfiles/cutBe14Bar20Be12.C");
						gROOT->ProcessLine(".x rootfiles/cutBe14Bar19Be12.C");
						gROOT->ProcessLine(".x rootfiles/cutBe14Bar18Be12.C");
						gROOT->ProcessLine(".x rootfiles/cutBe14Bar17Be12.C");
						gROOT->ProcessLine(".x rootfiles/cutBe14Bar16Be12.C");
						gROOT->ProcessLine(".x rootfiles/cutBe14Bar15Be12.C");
						gROOT->ProcessLine(".x rootfiles/cutBe14Bar14Be12.C");
						gROOT->ProcessLine(".x rootfiles/cutBe14Bar13Be12.C");
						gROOT->ProcessLine(".x rootfiles/cutBe14Bar12Be12.C");
						gROOT->ProcessLine(".x rootfiles/cutBe14Bar11Be12.C");
						gROOT->ProcessLine(".x rootfiles/cutBe14Bar10Be12.C");
						gROOT->ProcessLine(".x rootfiles/cutBe14Bar9Be12.C");
						gROOT->ProcessLine(".x rootfiles/cutBe14Bar8Be12.C");
						gROOT->ProcessLine(".x rootfiles/cutBe14Bar7Be12.C");

				}
				void loadHodBe14Be11(){
						gROOT->ProcessLine(".x rootfiles/cutBe14Bar23Be11.C");
						gROOT->ProcessLine(".x rootfiles/cutBe14Bar22Be11.C");
						gROOT->ProcessLine(".x rootfiles/cutBe14Bar21Be11.C");
						gROOT->ProcessLine(".x rootfiles/cutBe14Bar20Be11.C");
						gROOT->ProcessLine(".x rootfiles/cutBe14Bar19Be11.C");
				}


				void loadHodBe10He6(){
						gROOT->ProcessLine(".x rootfiles/cutBe10Bar26He6.C");
						gROOT->ProcessLine(".x rootfiles/cutBe10Bar27He6.C");
						gROOT->ProcessLine(".x rootfiles/cutBe10Bar27He6.C");
						gROOT->ProcessLine(".x rootfiles/cutBe10Bar28He6.C");
						gROOT->ProcessLine(".x rootfiles/cutBe10Bar29He6.C");
						gROOT->ProcessLine(".x rootfiles/cutBe10Bar30He6.C");
						gROOT->ProcessLine(".x rootfiles/cutBe10Bar31He6.C");
						gROOT->ProcessLine(".x rootfiles/cutBe10Bar32He6.C");
						gROOT->ProcessLine(".x rootfiles/cutBe10Bar33He6.C");
						gROOT->ProcessLine(".x rootfiles/cutBe10Bar34He6.C");
						gROOT->ProcessLine(".x rootfiles/cutBe10Bar35He6.C");
						gROOT->ProcessLine(".x rootfiles/cutBe10Bar36He6.C");

				}
				void loadHodBe10He4(){
						gROOT->ProcessLine(".x rootfiles/cutBe10Bar3He4.C");
						gROOT->ProcessLine(".x rootfiles/cutBe10Bar4He4.C");
						gROOT->ProcessLine(".x rootfiles/cutBe10Bar5He4.C");
						gROOT->ProcessLine(".x rootfiles/cutBe10Bar6He4.C");
						gROOT->ProcessLine(".x rootfiles/cutBe10Bar7He4.C");
						gROOT->ProcessLine(".x rootfiles/cutBe10Bar8He4.C");
						gROOT->ProcessLine(".x rootfiles/cutBe10Bar9He4.C");
						gROOT->ProcessLine(".x rootfiles/cutBe10Bar10He4.C");
						gROOT->ProcessLine(".x rootfiles/cutBe10Bar11He4.C");
						gROOT->ProcessLine(".x rootfiles/cutBe10Bar12He4.C");
						gROOT->ProcessLine(".x rootfiles/cutBe10Bar13He4.C");
						gROOT->ProcessLine(".x rootfiles/cutBe10Bar14He4.C");
						gROOT->ProcessLine(".x rootfiles/cutBe10Bar15He4.C");
						gROOT->ProcessLine(".x rootfiles/cutBe10Bar16He4.C");
						gROOT->ProcessLine(".x rootfiles/cutBe10Bar17He4.C");
						gROOT->ProcessLine(".x rootfiles/cutBe10Bar18He4.C");
						gROOT->ProcessLine(".x rootfiles/cutBe10Bar19He4.C");
						gROOT->ProcessLine(".x rootfiles/cutBe10Bar20He4.C");
						gROOT->ProcessLine(".x rootfiles/cutBe10Bar21He4.C");
						gROOT->ProcessLine(".x rootfiles/cutBe10Bar22He4.C");
						gROOT->ProcessLine(".x rootfiles/cutBe10Bar23He4.C");



				}

				void loadHodBe12He8(){

						gROOT->ProcessLine(".x rootfiles/cutBe12Bar28He8.C");
						gROOT->ProcessLine(".x rootfiles/cutBe12Bar29He8.C");
						gROOT->ProcessLine(".x rootfiles/cutBe12Bar30He8.C");
						gROOT->ProcessLine(".x rootfiles/cutBe12Bar31He8.C");
						gROOT->ProcessLine(".x rootfiles/cutBe12Bar32He8.C");
						gROOT->ProcessLine(".x rootfiles/cutBe12Bar33He8.C");
						gROOT->ProcessLine(".x rootfiles/cutBe12Bar34He8.C");
						gROOT->ProcessLine(".x rootfiles/cutBe12Bar35He8.C");
						gROOT->ProcessLine(".x rootfiles/cutBe12Bar36He8.C");

				}

				void loadHodBe12He6(){

						gROOT->ProcessLine(".x rootfiles/cutBe12Bar9He6.C");
						gROOT->ProcessLine(".x rootfiles/cutBe12Bar10He6.C");
						gROOT->ProcessLine(".x rootfiles/cutBe12Bar11He6.C");
						gROOT->ProcessLine(".x rootfiles/cutBe12Bar12He6.C");
						gROOT->ProcessLine(".x rootfiles/cutBe12Bar13He6.C");
						gROOT->ProcessLine(".x rootfiles/cutBe12Bar14He6.C");
						gROOT->ProcessLine(".x rootfiles/cutBe12Bar15He6.C");
						gROOT->ProcessLine(".x rootfiles/cutBe12Bar16He6.C");
						gROOT->ProcessLine(".x rootfiles/cutBe12Bar17He6.C");
						gROOT->ProcessLine(".x rootfiles/cutBe12Bar18He6.C");
						gROOT->ProcessLine(".x rootfiles/cutBe12Bar19He6.C");
						gROOT->ProcessLine(".x rootfiles/cutBe12Bar20He6.C");
						gROOT->ProcessLine(".x rootfiles/cutBe12Bar21He6.C");
						gROOT->ProcessLine(".x rootfiles/cutBe12Bar22He6.C");
						gROOT->ProcessLine(".x rootfiles/cutBe12Bar23He6.C");
						gROOT->ProcessLine(".x rootfiles/cutBe12Bar24He6.C");

				}


				void loadHodBe12He4(){
						gROOT->ProcessLine(".x rootfiles/cutBe12Bar15He4.C");
						gROOT->ProcessLine(".x rootfiles/cutBe12Bar14He4.C");
						gROOT->ProcessLine(".x rootfiles/cutBe12Bar13He4.C");
						gROOT->ProcessLine(".x rootfiles/cutBe12Bar12He4.C");
						gROOT->ProcessLine(".x rootfiles/cutBe12Bar11He4.C");
						gROOT->ProcessLine(".x rootfiles/cutBe12Bar10He4.C");
						gROOT->ProcessLine(".x rootfiles/cutBe12Bar9He4.C");
						gROOT->ProcessLine(".x rootfiles/cutBe12Bar8He4.C");
						gROOT->ProcessLine(".x rootfiles/cutBe12Bar7He4.C");
						gROOT->ProcessLine(".x rootfiles/cutBe12Bar6He4.C");
						gROOT->ProcessLine(".x rootfiles/cutBe12Bar5He4.C");
						gROOT->ProcessLine(".x rootfiles/cutBe12Bar4He4.C");
						gROOT->ProcessLine(".x rootfiles/cutBe12Bar3He4.C");
				}
				void loadHodBe14He4(){

                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar3He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar4He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar5He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar6He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar7He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar8He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar9He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar10He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar11He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar12He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar13He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar14He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar15He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar16He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar17He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar18He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar19He4.C");
				}
				void loadHodBe14He6(){

                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar11He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar12He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar13He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar14He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar15He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar16He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar17He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar18He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar19He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar20He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar21He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar22He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar23He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar24He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar26He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar27He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar28He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar29He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar30He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar31He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar32He6.C");

				}
				void loadHodBe14He8(){

                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar31He8.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar32He8.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar33He8.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar34He8.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar35He8.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar36He8.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar37He8.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar38He8.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar39He8.C");
				}


};
