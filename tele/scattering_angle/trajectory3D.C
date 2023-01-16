void trajectory3D(){
	static const int n_trajectories=4;
	vector<float> X1, X2, Y1, Y2, Z1, Z2;
	ifstream file_start;
	file_start.open("start.txt");
	float x = 0, y = 0, z = 0;

	while(1){
		file_start >> x >> y >> z;
		if (!file_start.good()) break;
		X1.push_back(x);
		Y1.push_back(y);
		Z1.push_back(z);
	}
	file_start.close();

	x=0.; y=0.; z=0.;

	ifstream file_end;
	file_end.open("stop.txt");
	while(1){
		file_end >> x >> y >> z;
		if (!file_end.good()) break;
		X2.push_back(10.*x);
		Y2.push_back(10.*y);
		Z2.push_back(10.*z);
	}
	file_end.close();

	TH3D *hdummy = new TH3D("hdummy", "", 2, -15, 15, 2, -15, 15, 2, -0.5, 20.5);
	hdummy->GetXaxis()->SetRangeUser(-15, 15);
	hdummy->GetYaxis()->SetRangeUser(-15, 15);
	hdummy->GetZaxis()->SetRangeUser(-0.5, 10);
	hdummy->SetLineColor(kWhite);	
	hdummy->Draw();

	TPolyLine3D *trajectories[n_trajectories];
//	//TPolyLine3D *test = new TPolyLine3D(2) [n_trajectories];
	for (int i=0; i<n_trajectories; ++i){
		trajectories[i] = new TPolyLine3D(2);
		trajectories[i]->SetPoint(0, X1[i], Y1[i], Z1[i]);
		trajectories[i]->SetPoint(1, X2[i], Y2[i], Z2[i]);
		trajectories[i]->Draw();
	}

}
