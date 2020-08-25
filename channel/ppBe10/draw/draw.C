class DrawTree{
	private:
		TChain *tree;
		TString var1;
		TString var2;
		int xBin;int xMin;int xMax;int yBin;int yMin;int yMax;
		TString gate;
		TString color;
		int side;
		int barId;
	public:
		DrawTree(){
			tree = new TChain("tree");
		}
		~DrawTree(){}
		void addFile(TString fileName){
			tree->Add(fileName);
		}
		void setVarName(TString v1,TString v2){
			var1 = v1;
			var2 = v2;
		}
		void setBar(int s,int b){
			side = s;
			barId = b;
		}
		void setVarRange(int xB,int xMi,int xMa,int yB,int yMi,int yMa){
			xBin = xB; xMin = xMi; xMax = xMa;
			yBin = yB; yMin = yMi; yMax = yMa;
		}
		void setGate(){
			gate = Form("espriHit==1&&espriHitSide==%d&&naiHit==1&&naiHitBarId==%d",side,barId);
		}
		void setColor(TString clr){
			color = clr;
		}
		void draw(){
			TString drawVar = var1+":"+var2+">>";
			TString drawName = Form("hBar%d_%d",side,barId);
			TString drawRange = Form("(%d,%d,%d,%d,%d,%d,%d)",xBin,xMin,xMax,yBin,yMin,yMax);
			tree->Draw(drawVar+drawName+drawRange,gate);
			//tree->Draw(drawVar+drawName+drawRange,gate,color);
		}
		void savePng(){
			gPad->Print(Form("png/Bar%d%d.png",side,barId));
		}
};
void drawNaiQPedVsAngle(int side,int barId){
	TString fileName = "../rootfiles_beforeCalib/ppBe10.root";
	TString var1 = "naiHitQPed";
	TString var2 = "espriAngle";
	//"naiHitQPed:espriAngle","espriHit==1&&espriHitSide==0&&naiHitBarId==0"
	DrawTree *dt = new DrawTree();	
	dt->addFile(fileName);
	dt->setVarName(var1,var2);
	dt->setBar(side,barId);
	dt->setVarRange(1000,50,80,1000,0,4000);
	dt->setGate();
	dt->setColor("colz");
	dt->draw();
	dt->savePng();
}
void drawNaiQPedVsAngle(){
	TCanvas *cPad = new TCanvas("cPad","cPad",1500,900);
	cPad->Divide(4,4);
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 7; ++j) {
	//for (int i = 0; i < 1; ++i) {
	//	for (int j = 0; j < 1; ++j) {
	
			cPad->cd(i*8+j+1);
			drawNaiQPedVsAngle(i,j);	
		}
	}
}
void draw(){
	drawNaiQPedVsAngle();
}
