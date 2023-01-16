void Merger::setBeamEvent(){
		beamEvent->init();
		beamEvent->load(plaEvent,bdcEvent);
		beamEvent->setEvent();
}
void Merger::printBeam(){
		beamEvent->print();
}
void Merger::setBeamOutputBranch(){
	beamEvent->setOutputBranch(tree);
}

