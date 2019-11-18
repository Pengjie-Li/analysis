void Merger::analysingESPRI(){
	
	// Analysing ESPRI data and select ESPRI LR side
	espriEvent->checkData(mergeESPRI);

	// load Target and beam to check Flight Length and Proton angle
	espriEvent->loadTargetPosition(vTarget);
	espriEvent->loadBeamVector(vBeam);
	espriEvent->setESPRIEvent();
}
void Merger::printESPRI(){
	mergeESPRI->print();
	espriEvent->print();	
}
void Merger::setESPRIOutputBranch(){
	mergeESPRI->setOutputBranch(tree);
	espriEvent->setOutputBranch(tree);
}
