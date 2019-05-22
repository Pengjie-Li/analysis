{
//========= Macro generated from object: stats/A special TPaveText to draw histogram statistics.
//========= by ROOT version5.34/20
   
   TPaveStats *ptstats = new TPaveStats(0.578518,0.534102,0.897822,0.903026,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetFillStyle(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   TText *text = ptstats->AddText("hQPlas1");
   text->SetTextSize(0.0484871);
   text = ptstats->AddText("Entries = 40000  ");
   text = ptstats->AddText("Mean  =   1370");
   text = ptstats->AddText("RMS   =  976.8");
   text = ptstats->AddText("Underflow = 3.624e+04");
   text = ptstats->AddText("Overflow  =      0");
   text = ptstats->AddText("Integral =   3755");
   ptstats->SetOptStat(1111111);
   ptstats->SetOptFit(111);
   ptstats->Draw();
}
