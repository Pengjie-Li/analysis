void Merger::printBDC(){
	mergeBDC->print();
	bdcEvent->print();
}
void Merger::analysingBDC(){

	bdcEvent->loadBDC(mergeBDC);
	bdcEvent->setBDCEvent();
}
void Merger::setBDCOutputBranch(){
	mergeBDC->setOutputBranch(tree);
	bdcEvent->setOutputBranch(tree);
}



