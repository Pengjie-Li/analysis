
void Merger::analysingHOD(){
	hodEvent->init();
	hodEvent->loadData(mergeHOD);
	hodEvent->setHodEvent();

}
void Merger::printHOD(){
	mergeHOD->print();
	hodEvent->print();
}
void Merger::setHODOutputBranch(){
	mergeHOD->setOutputBranch(tree);
	hodEvent->setOutputBranch(tree);
}
