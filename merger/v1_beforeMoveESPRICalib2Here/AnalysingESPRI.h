void Merger::analysingESPRI(){
	


	mergeESPRI->corrPlasTime(); // posidition dependency, time offset
	mergeESPRI->corrEnergy(); // posidition dependency, time offset

	// Analysing ESPRI data and select ESPRI LR side
	espriEvent->checkData(mergeESPRI);

	// load Target and beam to check Flight Length and Proton angle
	
	espriEvent->loadTargetPosition(bdcEvent->getTargetPosotion());
	espriEvent->loadBeamVector(bdcEvent->getBeamVector());
	
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
