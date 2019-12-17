void drawSTC(){
	TF1 *stc = new TF1("stc","[0]*sqrt(x)+[1]*x+[2]*x*x+[3]*x*x*x+[4]*x*x*x*x",-500,200);
	stc->SetParameters(-0.01495,0.006755,-1.754e-05,2.094e-08,-9.24e-12);
	stc->Draw();
	gPad->SetGridx();
	gPad->SetGridy();

}
