void Merger::analysingPLA(){
	plaEvent->analysing(mergePLA);		
	if(maxEventNumber<100) printPLA();
}
void Merger::printPLA(){
	mergePLA->print();
	plaEvent->print();
}
void Merger::setPLAOutputBranch(){

	//raw and cal
	mergePLA->setOutputBranch(tree);
	// analysed 
	plaEvent->setOutputBranch(tree);
}
