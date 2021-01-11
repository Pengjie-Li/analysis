void Merger::analysingTELE(){
	//teleEvent->loadTargetPosition(bdcEvent->getTargetPosotion());
	//teleEvent->loadBeamVector(bdcEvent->getBeamVector());
	teleEvent->init();
	teleEvent->loadTargetPosition(bdcEvent->getTargetPosotion());
	teleEvent->loadBeamVector(bdcEvent->getBeamVector());

	teleEvent->loadData(mergeTELE);
	teleEvent->setEvent();
	
}
void Merger::setTELEOutputBranch(){
	mergeTELE->setOutputBranch(tree);
	teleEvent->setOutputBranch(tree);
}
void Merger::printTELE(){
	mergeTELE->print();
	teleEvent->print();	
}
