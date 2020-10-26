{
	tree->Draw("teleDssdFE:teleCsiE>>hTele(1000,0,1000,1000,0,30)","teleHit==1&&dssdHit==1&&csiHit==1","colz");
	//tree->Draw("teleDssdE:1.8*teleCsiE>>hTele(500,0,1000,500,0,30)","teleHit==1&&teleHitCid[0]==4","colz");
	//tree->Draw("teleDssdE:teleCsiE>>hTele(500,0,1000,500,0,30)","teleHit==1&&teleHitCid[0]==5","colz");
	//gROOT->ProcessLine(".x drawCurveTeleDee.C");
	//gROOT->ProcessLine(".x cutAlpha.C");
}
