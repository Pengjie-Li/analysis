void barIdBe14(){
	int barArray[4]={29, 30, 31, 32};
	int countArray[4] = { 4231, 102179, 90331, 10544 };
	TGraph *gr = new TGraph(4,barArray, countArray);
	gr->SetMarkerStyle(5);
	gr->SetMarkerSize(3);
	gr->Draw("ap");
}
