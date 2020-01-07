void Merger::analysingTELE(){


	teleEvent->loadData(mergeTELE);
	teleEvent->loadTargetPosition(bdcEvent->getTargetPosotion());
	teleEvent->loadBeamVector(bdcEvent->getBeamVector());
	teleEvent->setTELEEvent();
	
}
void Merger::setTELEOutputBranch(){
	mergeTELE->setOutputBranch(tree);
	teleEvent->setOutputBranch(tree);
}
void Merger::printTELE(){
	mergeTELE->print();
	teleEvent->print();	
}
