class ESPRIDegraderPosition{
		private:
				Plane *leftPlane;
				Plane *rightPlane;
				TVector3 leftPedal;
				TVector3 rightPedal;
				TVector3 leftXBase;
				TVector3 rightXBase;

				void calPlaneLineIntersectPoint(double *returnResult,double *planeVector, double *planePoint, double *lineVector, double *linePoint){
						double vp1, vp2, vp3, n1, n2, n3, v1, v2, v3, m1, m2, m3, t,vpt;
						vp1 = planeVector[0];
						vp2 = planeVector[1];
						vp3 = planeVector[2];
						n1 = planePoint[0];
						n2 = planePoint[1];
						n3 = planePoint[2];
						v1 = lineVector[0];
						v2 = lineVector[1];
						v3 = lineVector[2];  
						m1 = linePoint[0];  
						m2 = linePoint[1];  
						m3 = linePoint[2];  
						vpt = v1 * vp1 + v2 * vp2 + v3 * vp3;  

						if (vpt == 0)  
						{  
								cout<<"Plane Parallel, not good!"<<endl;
						}
						else
						{
								t = ((n1 - m1) * vp1 + (n2 - m2) * vp2 + (n3 - m3) * vp3) / vpt;
								returnResult[0] = m1 + v1 * t;
								returnResult[1] = m2 + v2 * t;
								returnResult[2] = m3 + v3 * t;
						}
				}

				void vector2Array(TVector3 vector,double *array){
						array[0] = vector.X();
						array[1] = vector.Y();
						array[2] = vector.Z();
				}
				TVector3 calPlaneLineIntersectPoint(TVector3 planeVector,TVector3 planePoint,TVector3 lineVector,TVector3 linePoint){
						double planeVectorArray[3];
						vector2Array(planeVector,planeVectorArray);

						double planePointArray[3];
						vector2Array(planePoint,planePointArray);

						double lineVectorArray[3];
						vector2Array(lineVector,lineVectorArray);

						double linePointArray[3];
						vector2Array(linePoint,linePointArray);

						double returnResult[3];
						calPlaneLineIntersectPoint(returnResult,planeVectorArray,planePointArray,lineVectorArray,linePointArray);
						TVector3 vResult;
						vResult.SetXYZ(returnResult[0],returnResult[1],returnResult[2]);
						return vResult;

				}

		public:
				ESPRIDegraderPosition(){
						// Distance: 1188.17, 1187.47
						//leftPlane  = new Plane(-sqrt(3)/2,0.0,0.5,-1124.17);
						//rightPlane = new Plane(sqrt(3)/2,0.0,0.5,-1123.47);
						//leftPedal.SetXYZ(-973.559778,0.000000,562.085000);
						//rightPedal.SetXYZ(972.953560,0.000000,561.735000);
						//leftXBase.SetXYZ(0.500000,0.000000,sqrt(3)/2);
						//rightXBase.SetXYZ(0.500000,0.000000,-sqrt(3)/2);

						leftPlane  = new Plane(-0.864363,0.0,0.502869,-1124.18);
						rightPlane = new Plane(0.869150,0.0,0.494549,-1123.45);
						leftPedal.SetXYZ(-971.699128,0.000000,565.315379);
						rightPedal.SetXYZ(976.446434,0.000000,555.600814);
						leftXBase.SetXYZ(0.502869,0.000000,0.864363);
						rightXBase.SetXYZ(0.494549,0.000000,-0.869150);


				}
				~ESPRIDegraderPosition(){}
				TVector3 getDegraderPosition(int sideLR,TVector3 *espriPos,TVector3 *target){
						Plane *pl = NULL;
						if(sideLR==0) pl = leftPlane;
						else pl = rightPlane;

						TVector3 planeVector = pl->getPlaneVector();
						TVector3 planePoint  = pl->getPlanePoint();
						TVector3 lineVector  = (*espriPos)-(*target);
						TVector3 linePoint   = (*espriPos);
						return calPlaneLineIntersectPoint(planeVector,planePoint,lineVector,linePoint);

				}
				double getLocusXPosition(int side,TVector3 *degrader){
						TVector3 pedal;	TVector3 xBase;
						double offset;
						if(side == 0){
							pedal = leftPedal;
							xBase = leftXBase;
							//offset = 228;
							//offset = 230;
							offset = 0;
						}else{
							pedal = rightPedal;
							xBase = rightXBase;
							//offset = 230.5;
							//offset = 231;
							offset = 0;
						}
						return (((*degrader)-pedal).Dot(xBase)) + offset;
				}
};

class DegraderPosition{
		private:
				TVector3* degraderPosition;
				ESPRIDegraderPosition *dp;
		public:
				DegraderPosition(){
						degraderPosition = new TVector3;
						dp = new ESPRIDegraderPosition();
				}
				~DegraderPosition(){}
				double getPosition(int side,TVector3 *rdcPosition,TVector3 *targetPosition){
						(*degraderPosition) = dp->getDegraderPosition(side,rdcPosition,targetPosition);
						//(*degraderPosition).Print();
						//(*rdcPosition).Print();
						double xPos = dp->getLocusXPosition(side,degraderPosition);
						return xPos;
				}
};
