{
	//tree->Scan("teleAngle:teleLocusAngle:telePosition.X():telePosition.Y():telePosition.Z()");
	//tree->Scan("EventNumber:csiTHit:csiTRaw:csiQRaw:dssdTHit:dssdQRaw");
	tree->Scan("EventNumber:csiTHit:csiTRaw:csiQRaw:dssdTHit:dssdTHitSide:dssdTHitStripId:dssdTHitTCal:dssdQPed[0]:dssdQPed[1]:dssdQPed[2]:dssdQPed[3]", gate);
	//tree->Scan("EventNumber:teleHit:teleDssdE:teleCsiE:alphaEnergy", gate);
}
