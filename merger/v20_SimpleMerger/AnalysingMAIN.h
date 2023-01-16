
void Merger::analysingMAIN(){
		initAnalysedMAIN();

		Trig_DSB          = getCoincidenceTrigger() & 1;
		Trig_BxESPRIxTEL  = getCoincidenceTrigger() & 2;
		Trig_BxESPRI      = getCoincidenceTrigger() & 4;
		Trig_BxTEL        = getCoincidenceTrigger() & 8;
		Trig_BxHODP       = getCoincidenceTrigger() & 16;
		Trig_BxHODF       = getCoincidenceTrigger() & 32;
		Trig_BxNEBULA     = getCoincidenceTrigger() & 64;
	
}
void Merger::initAnalysedMAIN(){
	/********* Main Trig *********/
		Trig_DSB=-1;
		Trig_BxESPRIxTEL=-1;
		Trig_BxESPRI=-1;
		Trig_BxTEL=-1;
		Trig_BxHODP=-1;
		Trig_BxHODF=-1;
		Trig_BxNEBULA=-1;
}
void Merger::setMAINOutputBranch(){
	//raw and cal
	mergeMAIN->setOutputBranch(tree);

	tree->Branch("Trig_DSB"        ,&Trig_DSB        );
	tree->Branch("Trig_BxESPRIxTEL",&Trig_BxESPRIxTEL);
	tree->Branch("Trig_BxESPRI"    ,&Trig_BxESPRI    );
	tree->Branch("Trig_BxTEL"      ,&Trig_BxTEL      );
	tree->Branch("Trig_BxHODP"     ,&Trig_BxHODP     );
	tree->Branch("Trig_BxHODF"     ,&Trig_BxHODF     );
	tree->Branch("Trig_BxNEBULA"   ,&Trig_BxNEBULA   );
}
Int_t Merger::getCoincidenceTrigger(){
	return mergeMAIN->getCoincidenceTrigger();
}
