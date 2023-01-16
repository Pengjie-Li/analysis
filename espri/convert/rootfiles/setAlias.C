{
	CalTreeESPRI->SetAlias("plasBarQPed0","sqrt(plasQPed[0]*plasQPed[1])");
	CalTreeESPRI->SetAlias("plasBarQPed1","sqrt(plasQPed[2]*plasQPed[3])");
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 7; ++j) {

			CalTreeESPRI->SetAlias(Form("naiBarQPed%d%d",i,j),Form("sqrt(naiQPed[%d][%d]*naiQPed[%d][%d])",2*i,j,2*i+1,j));
		}

	}

}
