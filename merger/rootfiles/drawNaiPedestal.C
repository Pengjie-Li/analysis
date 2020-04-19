{

	for (int i = 0; i < 1; ++i) {
		for (int j = 0; j < 1; ++j) {
			tree->Draw(Form("naiQRaw[%d][%d]>>h_%d_%d(300,0,300)",i,j,i,j),"Trig_DSB");
		}
	}
}
