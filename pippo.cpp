void movebasil(){
	basil.target[0]=harryNow[0];
	basil.target[1]=harryNow[1];
    if(basil.direction==0){
        if(basil.target[1]>basil.now[1] && NoWall(basil.now,0) ){
			basil.now[1]++;
            basil.x+=mazepixel;
        }
        else if(!NoWall(basil.now,0)){
            if(basil.target[0]>basil.now[0] && NoWall(basil.now,3)){
                basil.direction=3;
				basil.now[0]++;
                basil.y-=mazepixel;
            }
            else if(basil.target[0]<basil.now[0] && NoWall(basil.now,2)){
                basil.direction=2;
				basil.now[0]--;
                basil.y+=mazepixel;
            }
			else if(basil.target[1]<basil.now[1] && NoWall(basil.now,1)){
				basil.direction=1;
				basil.now[1]--;
				basil.x-=mazepixel;
			}
			else if(NoWall(basil.now,3)){
				basil.direction=3;
				basil.now[0]++;
				basil.y-=mazepixel;
			}
			else if(NoWall(basil.now,2)){
				basil.direction=2;
				basil.now[0]--;
				basil.y+=mazepixel;
			}
			else if(NoWall(basil.now,1)){
				basil.direction=1;
				basil.now[1]--;
				basil.x-=mazepixel;
			}
        }
		else if(NoWall(basil.now,0)){
			if(basil.target[0]>basil.now[0] && NoWall(basil.now,3)){
                basil.direction=3;
				basil.now[0]++;
                basil.y-=mazepixel;
            }
            else if(basil.target[0]<basil.now[0] && NoWall(basil.now,2)){
                basil.direction=2;
				basil.now[0]--;
                basil.y+=mazepixel;
            }
			else{
				basil.direction=0;
				basil.now[1]++;
				basil.x+=mazepixel;
			}
		}
    }

	else if(basil.direction==1){
		if(basil.target[0]>basil.now[0] && NoWall(basil.now,3)){
			basil.direction=3;
			basil.now[0]++;
			basil.y-=mazepixel;
		}
        else if(basil.target[1]<basil.now[1] && NoWall(basil.now,1) ){
			basil.now[1]--;
            basil.x-=mazepixel;
        }
        else if(!NoWall(basil.now,1)){
            if(basil.target[0]>basil.now[0] && NoWall(basil.now,3)){
                basil.direction=3;
				basil.now[0]++;
                basil.y-=mazepixel;
            }
            else if(basil.target[0]<basil.now[0] && NoWall(basil.now,2)){
                basil.direction=2;
				basil.now[0]--;
                basil.y+=mazepixel;
            }
			else if(basil.target[1]>basil.now[1] && NoWall(basil.now,0)){
				basil.direction=0;
				basil.now[1]++;
				basil.x+=mazepixel;
			}
			else if(NoWall(basil.now,3)){
				basil.direction=3;
				basil.now[0]++;
				basil.y-=mazepixel;
			}
			else if(NoWall(basil.now,2)){
				basil.direction=2;
				basil.now[0]--;
				basil.y+=mazepixel;
			}
			else if(NoWall(basil.now,0)){
				basil.direction=0;
				basil.now[1]++;
				basil.x+=mazepixel;
			}
        }
		else if(NoWall(basil.now,1)){
			if(basil.target[0]>basil.now[0] && NoWall(basil.now,3)){
                basil.direction=3;
				basil.now[0]++;
                basil.y-=mazepixel;
            }
            else if(basil.target[0]<basil.now[0] && NoWall(basil.now,2)){
                basil.direction=2;
				basil.now[0]--;
                basil.y+=mazepixel;
            }
			else{
				basil.now[1]--;
				basil.x-=mazepixel;
			}
		}
    }
	
	else if(basil.direction==2){
		if(basil.target[1]<basil.now[1] && NoWall(basil.now,1)){
			basil.direction=1;
			basil.now[1]--;
			basil.x-=mazepixel;	
		}
        else if(basil.target[0]<basil.now[0] && NoWall(basil.now,2) ){
			basil.direction=2;
			basil.now[0]--;
            basil.y+=mazepixel;
        }
        else if(!NoWall(basil.now,2)){
            if(basil.target[1]>basil.now[1] && NoWall(basil.now,0)){
				basil.direction=0;
				basil.now[1]++;
				basil.x+=mazepixel;
			}
            else if(basil.target[1]<basil.now[1] && NoWall(basil.now,1)){
                basil.direction=1;
				basil.now[1]--;
                basil.x-=mazepixel;
            }
			else if(basil.target[0]>basil.now[0] && NoWall(basil.now,3)){
                basil.direction=3;
				basil.now[0]++;
                basil.y-=mazepixel;
            }
			else if(NoWall(basil.now,1)){
				basil.direction=1;
				basil.now[1]--;
				basil.x-=mazepixel;
			}
			else if(NoWall(basil.now,3)){
				basil.direction=3;
				basil.now[0]++;
				basil.y-=mazepixel;
			}
			else if(NoWall(basil.now,0)){
				basil.direction=0;
				basil.now[1]++;
				basil.x+=mazepixel;
			}
        }
		else if(NoWall(basil.now,2)){
			if(basil.target[1]>basil.now[1] && NoWall(basil.now,0)){
				basil.direction=0;
				basil.now[1]++;
				basil.x+=mazepixel;
			}
			else if(basil.target[1]<basil.now[1] && NoWall(basil.now,1)){
                basil.direction=1;
				basil.now[1]--;
                basil.x-=mazepixel;
            }
			else{
				basil.now[0]--;
				basil.y+=mazepixel;
			}
		}
    }

	else if(basil.direction==3){
		// if(basil.target[1]>dem1.now[1] && NoWall(basil.now,0)){
		// 	basil.direction=0;
		// 	basil.now[1]++;
		// 	basil.x+=mazepixel;	
		// }
        if(basil.target[0]>basil.now[0] && NoWall(basil.now,3) ){
			basil.now[0]++;
            basil.y-=mazepixel;
        }
        else if(!NoWall(basil.now,3 )){
            if(basil.target[0]<basil.now[0] && NoWall(basil.now,2)){
                basil.direction=2;
				basil.now[0]--;
                basil.y+=mazepixel;
            }
            else if(basil.target[1]<basil.now[1] && NoWall(basil.now,1)){
                basil.direction=1;
				basil.now[1]--;
                basil.x-=mazepixel;
            }
			else if(basil.target[1]>basil.now[1] && NoWall(basil.now,0)){
				basil.direction=0;
				basil.now[1]++;
				basil.x+=mazepixel;
			}
			else if(NoWall(basil.now,1)){
				basil.direction=1;
				basil.now[1]--;
				basil.x-=mazepixel;
			}
			else if(NoWall(basil.now,2)){
				basil.direction=2;
				basil.now[0]--;
				basil.y+=mazepixel;
			}
			else if(NoWall(basil.now,0)){
				basil.direction=0;
				basil.now[1]++;
				basil.x+=mazepixel;
			}
        }
		else if(NoWall(basil.now,3)){
			if(basil.target[1]>basil.now[1] && NoWall(basil.now,0)){
				basil.direction=0;
				basil.now[1]++;
				basil.x+=mazepixel;
			}
			else if(basil.target[1]<basil.now[1] && NoWall(basil.now,1)){
                basil.direction=1;
				basil.now[1]--;
                basil.x-=mazepixel;
            }
			else{
				basil.now[0]++;
				basil.y-=mazepixel;
			}
		}
    }	
}