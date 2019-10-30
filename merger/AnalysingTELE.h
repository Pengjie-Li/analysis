void Merger::analysingTELE(){

	getMultiplicity();

	teleEvent->loadData(mergeTELE);
	teleEvent->loadTargetPosition(vTarget);
	teleEvent->loadBeamVector(vBeam);
	teleEvent->setTELEEvent();
	//if(maxEventNumber <1000) teleEvent->print();	
	
}
void Merger::setTELEOutputBranch(){
	mergeTELE->setOutputBranch(tree);
	teleEvent->setOutputBranch(tree);
	//tree->Branch("multiplicity",&multiplicity,"multiplicity[4]/I");
}

void Merger::getMultiplicity(){

	//for(int i = 0;i<4;i++){
		//multiplicity[i] = getMultiplicity(i);	
	//}

	//if(maxEventNumber <100) printMultiplicity();	

}
void Merger::printMultiplicity(){
	//cout<<"Silicon Multiplicity: LF= "<<multiplicity[0]<<" LB= "<<multiplicity[1]<<" RF= "<<multiplicity[2]<<" RB= "<<multiplicity[4]<<endl;
}
Int_t Merger::getMultiplicity(int side){
	return mergeTELE->getMultiplicity(side);
}
