void Merger::analysingESPRI(){
	
	// Analysing ESPRI data and select ESPRI LR side
	//espriEvent->checkData(mergeESPRI);

	// load Target and beam to check Flight Length and Proton angle
	
	espriEvent->init();
	espriEvent->loadData(mergeESPRI);
	espriEvent->loadTargetPosition(bdcEvent->getTargetPosotion());
	espriEvent->loadBeamVector(bdcEvent->getBeamVector());
	espriEvent->loadBeamToF(beamEvent->getBeamToF());
	
	espriEvent->setESPRIEvent();

}
void Merger::printESPRI(){
	if(mergeESPRI->isGoodEvent()){
		mergeESPRI->print();
		espriEvent->print();	
	}
}
void Merger::setESPRIOutputBranch(){
	mergeESPRI->setOutputBranch(tree);
	espriEvent->setOutputBranch(tree);
}
