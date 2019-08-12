{
	TLine *Protonx = new TLine(-100,1570,1000,1570);
	Protonx->SetLineWidth(1);
	Protonx->SetLineColor(2);
	Protonx->Draw();

	TLine *Deutronx = new TLine(-100,2092.7,1000,2092.7);
	Deutronx->SetLineWidth(1);
	Deutronx->SetLineColor(2);
	Deutronx->Draw();

	TLine *Tritonx = new TLine(-100,2490.6,1000,2490.6);
	Tritonx->SetLineWidth(1);
	Tritonx->SetLineColor(2);
	Tritonx->Draw();






	TLine *He4x = new TLine(-100,7370,1000,7370);
	He4x->SetLineWidth(1);
	He4x->SetLineColor(2);
	He4x->Draw();

	TLine *He4y = new TLine(463.46,-100,463.46,35000);
	He4y->SetLineWidth(1);
	He4y->SetLineColor(2);
	He4y->Draw();

	TLine *Li7x = new TLine(-100,17830,1000,17830);
	Li7x->SetLineWidth(1);
	Li7x->SetLineColor(2);
	Li7x->Draw();

	TLine *Li7y = new TLine(732.48,-100,732.48,35000);
	Li7y->SetLineWidth(1);
	Li7y->SetLineColor(2);
	Li7y->Draw();




}
