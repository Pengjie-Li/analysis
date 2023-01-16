void Merger::setAlphaEvent(){
	alphaEvent->init();

	alphaEvent->load(teleEvent);
	alphaEvent->setEvent();

}
void Merger::printAlpha(){
	if(alphaEvent->isGoodEvent()) alphaEvent->print();
}
void Merger::setAlphaOutputBranch(){
	alphaEvent->setOutputBranch(tree);
}
