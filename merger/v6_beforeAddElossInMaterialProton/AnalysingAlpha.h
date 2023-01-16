void Merger::setAlphaEvent(){
	alphaEvent->init();

	alphaEvent->loadTargetPosition(bdcEvent->getTargetPosotion());
	alphaEvent->loadBeamVector(bdcEvent->getBeamVector());
	alphaEvent->load(teleEvent);
	alphaEvent->setEvent();

}
void Merger::printAlpha(){
	if(alphaEvent->isGoodEvent()) alphaEvent->print();
}
void Merger::setAlphaOutputBranch(){
	alphaEvent->setOutputBranch(tree);
}
