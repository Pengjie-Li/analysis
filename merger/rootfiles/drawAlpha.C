{
	//tree->Draw("teleDssdE:teleCsiE>>hTele(500,0,1000,500,5,30)","teleHit==1","colz");
	//tree->Draw("teleDssdE:teleCsiE>>hTele(500,0,1000,500,5,30)",gate,"colz");
	//tree->Draw("teleDssdE:teleCsiE>>hTele(500,0,1000,500,5,30)","teleHit==1&&telePosition.X()>0","colz");
	//tree->Draw("teleDssdE:teleCsiE>>hTele(500,0,1000,500,5,30)","teleHit==1&&telePosition.X()<0","colz");
	//tree->Draw("teleDssdFE:teleCsiE>>hTele(1000,0,1000,1000,0,30)","teleHit==1","colz");
	//tree->Draw("teleDssdE:1.8*teleCsiE>>hTele(500,0,1000,500,0,30)","teleHit==1&&teleHitCid[0]==4","colz");
	tree->Draw("teleDssdE:teleCsiE>>hTele(500,0,1000,500,0,30)","teleHit==1&&teleHitCid[0]==4","colz");
	//tree->Draw("teleDssdE:teleCsiE>>hTele(500,0,1000,500,0,30)","teleHit==1&&teleHitCid[0]==5","colz");
	gROOT->ProcessLine(".x drawCurveTeleDee.C");
	gROOT->ProcessLine(".x cutAlpha.C");
}
