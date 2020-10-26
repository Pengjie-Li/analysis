void Merger::setProtonEvent(){
	protonEvent->init();
	protonEvent->load(espriEvent);
	protonEvent->setEvent();

}
void Merger::printProton(){
	if(protonEvent->isGoodEvent()) protonEvent->print();
}
void Merger::setProtonOutputBranch(){
	protonEvent->setOutputBranch(tree);
}
