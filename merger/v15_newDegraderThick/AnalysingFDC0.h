void Merger::printFDC0(){
	mergeFDC0->print();
	fdc0Event->print();
}
void Merger::analysingFDC0(){

	fdc0Event->loadFDC0(mergeFDC0);
	fdc0Event->loadTargetPosition(bdcEvent->getTargetPosotion());
	fdc0Event->loadBeamVector(bdcEvent->getBeamVector());
	fdc0Event->setFDC0Event();
}
void Merger::setFDC0OutputBranch(){
	mergeFDC0->setOutputBranch(tree);
	fdc0Event->setOutputBranch(tree);
}
