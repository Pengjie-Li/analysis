Double_t tdc2mm[8][5000]={0};
Double_t tdcint[8]={0};
Int_t tdcwindow[2]={1700,1870};
void SetDriftLength(TH1 * inhtdc, Int_t layer_id) {

	// tdcint store total counts for each layer
	tdcint[layer_id] = (Double_t)inhtdc->Integral(inhtdc->FindBin(tdcwindow[0]),
			inhtdc->FindBin(tdcwindow[1])); 
	if(tdcwindow[0]<0){ // in the case of v1190/v1290 case
		for(Int_t i=0;i<5000;i++){
			Int_t tdcbin = i+tdcwindow[0];
			if(tdcbin>tdcwindow[1] || tdcbin<tdcwindow[0]) tdc2mm[layer_id][i] = 0;
			else tdc2mm[layer_id][i] = 5 * 0.5 * (Double_t)inhtdc->Integral(inhtdc->FindBin(tdcwindow[0]),inhtdc->FindBin(tdcbin))/tdcint[layer_id];
		}
	}
	else{ // otherwize change it to array 
		for(Int_t i=0;i<5000;i++){
			if(i>tdcwindow[1] || i<tdcwindow[0]) tdc2mm[layer_id][i] = 0;
			else tdc2mm[layer_id][i] = 5 * 0.5 * (Double_t)inhtdc->Integral(inhtdc->FindBin(i),inhtdc->FindBin(tdcwindow[1]))/tdcint[layer_id];
		}
	}
}

Double_t CalcDriftLength(Int_t tdc, Int_t layer_id = -1) {

	if(tdcint[layer_id]>0){ // if tdc distribution is set, calculation by using tdc distribution
		if(tdc>tdcwindow[1] || tdc<tdcwindow[0]) return -9999;
		if(tdcwindow[0]<0) // in the case of v1190/v1290. 
			return tdc2mm[layer_id][tdc-tdcwindow[0]];
		return tdc2mm[layer_id][tdc];
	}

	return -9999;

}

