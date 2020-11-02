#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <sstream>
#include <stdlib.h>
using namespace std;

//Ofstream Variables
ofstream lexFileDi, lexFileCode, lexFileDes, lexFilePr;
ofstream troFileDi, troFileCode, troFileDes, troFilePr;
ofstream phiFileDi, phiFileCode, phiFileDes, phiFilePr;
ofstream artFileDi, artFileCode, artFileDes, artFilePr;
ofstream epiFileDi, epiFileCode, epiFileDes, epiFilePr;
ofstream salFileDi, salFileCode, salFileDes, salFilePr;
ofstream madeFileDi, madeFileCode, madeFileDes, madeFilePr;
ofstream parFileDi, parFileCode, parFileDes, parFilePr;
//----------------------------------------------------------------

//global variables
bool found;
//-----------------


class lexonTree{

	public:
		class lexonNode{
		public:
			string lexDi;
			string lexCode;
			string lexDes;
			double lexWho;
			double lexSale;
			int lexPie;

			lexonNode *lexRight;
			lexonNode *lexLeft;

		}*lexRoot;

		lexonTree(){ lexRoot = NULL; }

		void addItemLex(string lDi, string lCode, string lDes, double lWho, double lSale, int lPie){
			lexonNode *current;
			current = lexRoot;
			if(lexRoot == NULL){
				lexRoot = newNodeLex(lDi, lCode, lDes, lWho, lSale, lPie);
				return;
			}
			while(1){
				if(lCode < current->lexCode){
					if(current->lexLeft == NULL){
						current->lexLeft = newNodeLex(lDi, lCode, lDes, lWho, lSale, lPie);
						return;
					}
					else {
					current = current->lexLeft;
					}
				}
				if(lCode >= current->lexCode){
					if(current->lexRight == NULL){
						current->lexRight = newNodeLex(lDi, lCode, lDes, lWho, lSale, lPie);
						return;
					}
					else {
					current = current->lexRight;
					}
				}
			}
		}

		lexonNode *newNodeLex(string lDi, string lCode, string lDes, double lWho, double lSale, int lPie){
			lexonNode *neos;
			neos = new(nothrow) lexonNode;
			neos->lexDi = lDi;
			neos->lexCode = lCode;
			neos->lexDes = lDes;
			neos->lexWho = lWho;
			neos->lexSale = lSale;
			neos->lexPie = lPie;
			neos->lexRight = NULL;
			neos->lexLeft = NULL;
			return (neos);
		}

		void lexDisplay(lexonNode *lptr){
			int length;
			stringstream ssWho;
			stringstream ssSale;
			string strWho;
			string strSale;
			if(lptr == NULL) return;
			else{
				lexDisplay(lptr->lexLeft);
				cout << "| ";
				cout << lptr->lexDi;
				for(length = 0; length < 16 - lptr->lexDi.size(); length++) cout << " ";
				cout << "| ";
				cout << lptr->lexCode;
				for(length = 0; length < 18 - lptr->lexCode.size(); length++) cout << " ";
				cout << "| ";
				cout << lptr->lexDes;
				for(length = 0; length < 20 - lptr->lexDes.size(); length++) cout << " ";
				cout << "| ";
				cout << lptr->lexWho;
				ssWho << lptr->lexWho;
				strWho = ssWho.str();
				for(length = 0; length < 24 - strWho.size(); length++) cout << " ";
				cout << "| ";
				cout << lptr->lexSale;
				ssSale << lptr->lexSale;
				strSale = ssSale.str();
				for(length = 0; length < 22 - strSale.size(); length++) cout << " ";
				cout << "| ";
				cout << lptr->lexPie;
				cout << "\n_______________________________________________________________________________________________________________________\n\n";
				lexDisplay(lptr->lexRight);
			}
		}

        void lexDisplayOne(string lCode, lexonNode *lptr){
                int length;
                stringstream ssWho;
                stringstream ssSale;
                string strWho;
                string strSale;
                if(lptr == NULL) return;
                else{
                lexDisplayOne(lCode, lptr->lexLeft);
                if(lCode == lptr->lexCode){
                    cout << "\n___________________________________________________________________________________________\n\n";
                    cout << "| ";
                    cout << lptr->lexDi;
                    for(length = 0; length < 16 - lptr->lexDi.size(); length++) cout << " ";
                    cout << "| ";
                    cout << lptr->lexCode;
                    for(length = 0; length < 16 - lptr->lexCode.size(); length++) cout << " ";
                    cout << "| ";
                    cout << lptr->lexDes;
                    for(length = 0; length < 16 - lptr->lexDes.size(); length++) cout << " ";
                    cout << "| ";
                    cout << lptr->lexWho;
                    ssWho << lptr->lexWho;
                    strWho = ssWho.str();
                    for(length = 0; length < 10 - strWho.size(); length++) cout << " ";
                    cout << "| ";
                    cout << lptr->lexSale;
                    ssSale << lptr->lexSale;
                    strSale = ssSale.str();
                    for(length = 0; length < 10 - strSale.size(); length++) cout << " ";
                    cout << "| ";
                    cout << lptr->lexPie;
                    cout << "\n___________________________________________________________________________________________\n\n";
                }
                    lexDisplayOne(lCode, lptr->lexRight);

            }
        }

		void lexDisplayFile(lexonNode *lptr){
			if(lptr == NULL) return;
			else{
				lexFileDi << lptr->lexDi << endl;
				lexFileCode << lptr->lexCode << endl;
				lexFileDes << lptr->lexDes << endl;
				lexFilePr << lptr->lexWho << " " << lptr->lexSale << " " << lptr->lexPie << endl;
				lexDisplayFile(lptr->lexLeft);
				lexDisplayFile(lptr->lexRight);
			}
		}

		void saveLexData(){
			string lineDi;
			string lineCode;
			string lineDes;
			double fileWho;
			double fileSale;
			int filePie;

			ifstream lexDiFile;
			ifstream lexCodeFile;
			ifstream lexDesFile;
			ifstream lexPriceStockFile;

			lexDiFile.open("LEXON_Di.txt");
			lexCodeFile.open("LEXON_code.txt");
			lexDesFile.open("LEXON_description.txt");
			lexPriceStockFile.open("LEXON_price_stock.txt");

			while(!lexDiFile.eof() && !lexCodeFile.eof() && !lexDesFile.eof() && !lexPriceStockFile.eof()){
				getline(lexDiFile, lineDi);
				getline(lexCodeFile, lineCode);
				getline(lexDesFile, lineDes);
				lexPriceStockFile >> fileWho >> fileSale >> filePie;
				if(lineDi == "" || lineCode == "" || lineDes == "") continue;
				addItemLex(lineDi, lineCode, lineDes, fileWho, fileSale, filePie);
			}

			lexDiFile.close();
			lexCodeFile.close();
			lexDesFile.close();
			lexPriceStockFile.close();


		}

        void changeLexPiece(string lCode, lexonNode *lptr, int newPiece){
            if(lptr == NULL) return;
            else{
                changeLexPiece(lCode, lptr->lexLeft, newPiece);
                if(lCode == lptr->lexCode){
                    lptr->lexPie = newPiece;
                }
                changeLexPiece(lCode, lptr->lexRight, newPiece);
            }
        }

        void findLexCode(string lCode, lexonNode *lptr){
            if(lptr == NULL) return;
            else{
                findLexCode(lCode, lptr->lexLeft);
                if(lCode == lptr->lexCode){
                    found = true;
                    return;
                }
                findLexCode(lCode, lptr->lexRight);
            }
        }

        void toRestoreDisplay(lexonNode *lptr){
            if(lptr == NULL) return;
            else{
                toRestoreDisplay(lptr->lexLeft);
                if(lptr->lexPie < 2){
                    lexDisplayOne(lptr->lexCode, lptr);
                }
                toRestoreDisplay(lptr->lexRight);
            }
        }

        void lexDeleteNode(string lCode){
            lexonNode *current;
            lexonNode *preRight;
            lexonNode *preLeft;
            lexonNode *temp;
            lexonNode *extraTemp;
            current = lexRoot;
            while(1){
				if(lCode < current->lexCode){
				    preLeft = current;
				    preRight = NULL;
				    current = current->lexLeft;
				}
				else if(lCode > current->lexCode){
                    preRight = current;
                    preLeft = NULL;
                    current = current->lexRight;
				}
				else if(lCode == current->lexCode) break;
			}
			if(current->lexRight == NULL && current->lexLeft == NULL  && current != lexRoot){
                if(preLeft == NULL){
                    preRight->lexRight = NULL;
                    delete current;
                    return;
                }
                else if(preRight == NULL){
                    preLeft->lexLeft = NULL;
                    delete current;
                    return;
                }
			}
			else if(current->lexRight == NULL && current->lexLeft != NULL  && current != lexRoot){
                if(preLeft == NULL){
                    temp = current;
                    temp = temp->lexLeft;
                    preRight->lexRight = temp;
                    delete current;
                    return;
                }
                else if(preRight == NULL){
                    temp = current;
                    temp = temp->lexLeft;
                    preLeft->lexLeft = temp;
                    delete current;
                    return;
                }
			}
			else if(current->lexRight != NULL && current->lexLeft == NULL  && current != lexRoot){
                if(preLeft == NULL){
                    temp = current;
                    temp = temp->lexRight;
                    preRight->lexRight = temp;
                    delete current;
                    return;
                }
                else if(preRight == NULL){
                    temp = current;
                    temp = temp->lexRight;
                    preLeft->lexLeft = temp;
                    delete current;
                    return;
                }
			}
			else if(current->lexRight != NULL && current->lexLeft != NULL && current != lexRoot){
                if(preLeft == NULL){
                    temp = current;
                    temp = temp->lexRight;
                    if(temp->lexLeft == NULL){
                        preRight->lexRight = temp;
                        temp->lexLeft = current->lexLeft;
                        delete current;
                        return;
                    }
                    else if(temp->lexLeft != NULL){
                        while(temp->lexLeft != NULL){
                            preRight = temp;
                            temp = temp->lexLeft;
                        }
                        current->lexDi = temp->lexDi;
                        current->lexCode = temp->lexCode;
                        current->lexDes = temp->lexDes;
                        current->lexWho = temp->lexWho;
                        current->lexSale = temp->lexSale;
                        current->lexPie = temp->lexPie;
                        if(temp->lexRight == NULL){
                            preRight->lexLeft = NULL;
                            delete temp;
                            return;
                        }
                        else if(temp->lexRight != NULL){
                            extraTemp = temp;
                            extraTemp = extraTemp->lexRight;
                            preRight->lexLeft = extraTemp;
                            delete temp;
                            return;
                        }
                    }
                }
                else if(preRight == NULL){
                    temp = current;
                    temp = temp->lexRight;
                    if(temp->lexLeft == NULL){
                        preLeft->lexLeft = temp;
                        temp->lexLeft = current->lexLeft;
                        delete current;
                        return;
                    }
                    else if(temp->lexLeft != NULL){
                        while(temp->lexLeft != NULL){
                            preLeft = temp;
                            temp = temp->lexLeft;
                        }
                        current->lexDi = temp->lexDi;
                        current->lexCode = temp->lexCode;
                        current->lexDes = temp->lexDes;
                        current->lexWho = temp->lexWho;
                        current->lexSale = temp->lexSale;
                        current->lexPie = temp->lexPie;
                        if(temp->lexRight == NULL){
                            preLeft->lexLeft = NULL;
                            delete temp;
                            return;
                        }
                        else if(temp->lexRight != NULL){
                            extraTemp = temp;
                            extraTemp = extraTemp->lexRight;
                            preLeft->lexLeft = extraTemp;
                            delete temp;
                            return;
                        }
                    }
                }
			}
			else if(current == lexRoot){
                temp = current;
                temp = current->lexRight;
                if(temp == NULL){
                    lexRoot = current->lexLeft;
                    delete current;
                    return;
                }
                else if(temp != NULL){
                    if(temp->lexLeft == NULL){
                        temp->lexLeft = current->lexLeft;
                        lexRoot = temp;
                        delete current;
                        return;
                    }
                    else if(temp->lexLeft != NULL){
                        while(temp->lexLeft != NULL){
                            extraTemp = temp;
                            temp = temp->lexLeft;
                        }
                        current->lexDi = temp->lexDi;
                        current->lexCode = temp->lexCode;
                        current->lexDes = temp->lexDes;
                        current->lexWho = temp->lexWho;
                        current->lexSale = temp->lexSale;
                        current->lexPie = temp->lexPie;
                        if(temp->lexRight == NULL){
                            extraTemp->lexLeft = NULL;
                            delete temp;
                            return;
                        }
                        else if(temp->lexRight != NULL){
                            extraTemp->lexLeft = temp->lexRight;
                            delete temp;
                            return;
                        }
                    }
                }
			}

        }


};



class troikaTree{

	public:
		class troikaNode{
		public:
			string troDi;
			string troCode;
			string troDes;
			double troWho;
			double troSale;
			double troPie;

			troikaNode *troRight;
			troikaNode *troLeft;

		}*troRoot;

		troikaTree(){ troRoot = NULL; }

		void addItemTro(string tDi, string tCode, string tDes, double tWho, double tSale, int tPie){
			troikaNode *current;
			current = troRoot;
			if(troRoot == NULL){
				troRoot = newNodeTro(tDi, tCode, tDes, tWho, tSale, tPie);
				return;
			}
			while(1){
				if(tCode < current->troCode){
					if(current->troLeft == NULL){
						current->troLeft = newNodeTro(tDi, tCode, tDes, tWho, tSale, tPie);
						return;
					}
					else {
					current = current->troLeft;
					}
				}
				if(tCode >= current->troCode){
					if(current->troRight == NULL){
						current->troRight = newNodeTro(tDi, tCode, tDes, tWho, tSale, tPie);
						return;
					}
					else {
					current = current->troRight;
					}
				}
			}
		}

		troikaNode *newNodeTro(string tDi, string tCode, string tDes, double tWho, double tSale, int tPie){
			troikaNode *neos;
			neos = new(nothrow) troikaNode;
			neos->troDi = tDi;
			neos->troCode = tCode;
			neos->troDes = tDes;
			neos->troWho = tWho;
			neos->troSale = tSale;
			neos->troPie = tPie;
			neos->troRight = NULL;
			neos->troLeft = NULL;
			return (neos);
		}

		void troDisplay(troikaNode *tptr){
			int length;
			stringstream ssWho;
			stringstream ssSale;
			string strWho;
			string strSale;
			if(tptr == NULL) return;
			else{
				troDisplay(tptr->troLeft);
				cout << "| ";
				cout << tptr->troDi;
				for(length = 0; length < 16 - tptr->troDi.size(); length++) cout << " ";
				cout << "| ";
				cout << tptr->troCode;
				for(length = 0; length < 18 - tptr->troCode.size(); length++) cout << " ";
				cout << "| ";
				cout << tptr->troDes;
				for(length = 0; length < 20 - tptr->troDes.size(); length++) cout << " ";
				cout << "| ";
				cout << tptr->troWho;
				ssWho << tptr->troWho;
				strWho = ssWho.str();
				for(length = 0; length < 24 - strWho.size(); length++) cout << " ";
				cout << "| ";
				cout << tptr->troSale;
				ssSale << tptr->troSale;
				strSale = ssSale.str();
				for(length = 0; length < 22 - strSale.size(); length++) cout << " ";
				cout << "| ";
				cout << tptr->troPie;
				cout << "\n_______________________________________________________________________________________________________________________\n\n";
				troDisplay(tptr->troRight);
			}
		}


		void saveTroData(){
			string lineDi;
			string lineCode;
			string lineDes;
			double fileWho;
			double fileSale;
			int filePie;

			ifstream troDiFile;
			ifstream troCodeFile;
			ifstream troDesFile;
			ifstream troPriceStockFile;

			troDiFile.open("TROIKA_Di.txt");
			troCodeFile.open("TROIKA_code.txt");
			troDesFile.open("TROIKA_description.txt");
			troPriceStockFile.open("TROIKA_price_stock.txt");

			while(!troDiFile.eof() && !troCodeFile.eof() && !troDesFile.eof() && !troPriceStockFile.eof()){
				getline(troDiFile, lineDi);
				getline(troCodeFile, lineCode);
				getline(troDesFile, lineDes);
				troPriceStockFile >> fileWho >> fileSale >> filePie;
				if(lineDi == "" || lineCode == "" || lineDes == "") continue;
				addItemTro(lineDi, lineCode, lineDes, fileWho, fileSale, filePie);
			}

			troDiFile.close();
			troCodeFile.close();
			troDesFile.close();
			troPriceStockFile.close();


		}

        void changeTroPiece(string tCode, troikaNode *tptr, int newPiece){
            if(tptr == NULL) return;
            else{
                changeTroPiece(tCode, tptr->troLeft, newPiece);
                if(tCode == tptr->troCode){
                    tptr->troPie = newPiece;
                }
                changeTroPiece(tCode, tptr->troRight, newPiece);
            }
        }

        void findTroCode(string tCode, troikaNode *tptr){
            if(tptr == NULL) return;
            else{
                findTroCode(tCode, tptr->troLeft);
                if(tCode == tptr->troCode){
                    found = true;
                    return;
                }
                findTroCode(tCode, tptr->troRight);
            }
        }

        void troDisplayOne(string tCode, troikaNode *tptr){
                int length;
                stringstream ssWho;
                stringstream ssSale;
                string strWho;
                string strSale;
                if(tptr == NULL) return;
                else{
                troDisplayOne(tCode, tptr->troLeft);
                if(tCode == tptr->troCode){
                    cout << "\n___________________________________________________________________________________________\n\n";
                    cout << "| ";
                    cout << tptr->troDi;
                    for(length = 0; length < 16 - tptr->troDi.size(); length++) cout << " ";
                    cout << "| ";
                    cout << tptr->troCode;
                    for(length = 0; length < 16 - tptr->troCode.size(); length++) cout << " ";
                    cout << "| ";
                    cout << tptr->troDes;
                    for(length = 0; length < 16 - tptr->troDes.size(); length++) cout << " ";
                    cout << "| ";
                    cout << tptr->troWho;
                    ssWho << tptr->troWho;
                    strWho = ssWho.str();
                    for(length = 0; length < 10 - strWho.size(); length++) cout << " ";
                    cout << "| ";
                    cout << tptr->troSale;
                    ssSale << tptr->troSale;
                    strSale = ssSale.str();
                    for(length = 0; length < 10 - strSale.size(); length++) cout << " ";
                    cout << "| ";
                    cout << tptr->troPie;
                    cout << "\n___________________________________________________________________________________________\n\n";
                }
                    troDisplayOne(tCode, tptr->troRight);

            }
        }

        void troDisplayFile(troikaNode *tptr){
			if(tptr == NULL) return;
			else{
				troFileDi << tptr->troDi << endl;
				troFileCode << tptr->troCode << endl;
				troFileDes << tptr->troDes << endl;
				troFilePr << tptr->troWho << " " << tptr->troSale << " " << tptr->troPie << endl;
				troDisplayFile(tptr->troLeft);
				troDisplayFile(tptr->troRight);
			}
		}

        void toRestoreDisplay(troikaNode *tptr){
            if(tptr == NULL) return;
            else{
                toRestoreDisplay(tptr->troLeft);
                if(tptr->troPie < 2){
                    troDisplayOne(tptr->troCode, tptr);
                }
                toRestoreDisplay(tptr->troRight);
            }
        }


        void troDeleteNode(string tCode){
            troikaNode *current;
            troikaNode *preRight;
            troikaNode *preLeft;
            troikaNode *temp;
            troikaNode *extraTemp;
            current = troRoot;
            while(1){
				if(tCode < current->troCode){
				    preLeft = current;
				    preRight = NULL;
				    current = current->troLeft;
				}
				else if(tCode > current->troCode){
                    preRight = current;
                    preLeft = NULL;
                    current = current->troRight;
				}
				else if(tCode == current->troCode) break;
			}
			if(current->troRight == NULL && current->troLeft == NULL && current != troRoot){
                if(preLeft == NULL){
                    preRight->troRight = NULL;
                    delete current;
                    return;
                }
                else if(preRight == NULL){
                    preLeft->troLeft = NULL;
                    delete current;
                    return;
                }
			}
			else if(current->troRight == NULL && current->troLeft != NULL && current != troRoot){
                if(preLeft == NULL){
                    temp = current;
                    temp = temp->troLeft;
                    preRight->troRight = temp;
                    delete current;
                    return;
                }
                else if(preRight == NULL){
                    temp = current;
                    temp = temp->troLeft;
                    preLeft->troLeft = temp;
                    delete current;
                    return;
                }
			}
			else if(current->troRight != NULL && current->troLeft == NULL && current != troRoot){
                if(preLeft == NULL){
                    temp = current;
                    temp = temp->troRight;
                    preRight->troRight = temp;
                    delete current;
                    return;
                }
                else if(preRight == NULL){
                    temp = current;
                    temp = temp->troRight;
                    preLeft->troLeft = temp;
                    delete current;
                    return;
                }
			}
			else if(current->troRight != NULL && current->troLeft != NULL && current != troRoot){
                if(preLeft == NULL){
                    temp = current;
                    temp = temp->troRight;
                    if(temp->troLeft == NULL){
                        preRight->troRight = temp;
                        temp->troLeft = current->troLeft;
                        delete current;
                        return;
                    }
                    else if(temp->troLeft != NULL){
                        while(temp->troLeft != NULL){
                            preRight = temp;
                            temp = temp->troLeft;
                        }
                        current->troDi = temp->troDi;
                        current->troCode = temp->troCode;
                        current->troDes = temp->troDes;
                        current->troWho = temp->troWho;
                        current->troSale = temp->troSale;
                        current->troPie = temp->troPie;
                        if(temp->troRight == NULL){
                            preRight->troLeft = NULL;
                            delete temp;
                            return;
                        }
                        else if(temp->troRight != NULL){
                            extraTemp = temp;
                            extraTemp = extraTemp->troRight;
                            preRight->troLeft = extraTemp;
                            delete temp;
                            return;
                        }
                    }
                }
                else if(preRight == NULL){
                    temp = current;
                    temp = temp->troRight;
                    if(temp->troLeft == NULL){
                        preLeft->troLeft = temp;
                        temp->troLeft = current->troLeft;
                        delete current;
                        return;
                    }
                    else if(temp->troLeft != NULL){
                        while(temp->troLeft != NULL){
                            preLeft = temp;
                            temp = temp->troLeft;
                        }
                        current->troDi = temp->troDi;
                        current->troCode = temp->troCode;
                        current->troDes = temp->troDes;
                        current->troWho = temp->troWho;
                        current->troSale = temp->troSale;
                        current->troPie = temp->troPie;
                        if(temp->troRight == NULL){
                            preLeft->troLeft = NULL;
                            delete temp;
                            return;
                        }
                        else if(temp->troRight != NULL){
                            extraTemp = temp;
                            extraTemp = extraTemp->troRight;
                            preLeft->troLeft = extraTemp;
                            delete temp;
                            return;
                        }
                    }
                }
			}
			else if(current == troRoot){
                temp = current;
                temp = current->troRight;
                if(temp == NULL){
                    troRoot = current->troLeft;
                    delete current;
                    return;
                }
                else if(temp != NULL){
                    if(temp->troLeft == NULL){
                        temp->troLeft = current->troLeft;
                        troRoot = temp;
                        delete current;
                        return;
                    }
                    else if(temp->troLeft != NULL){
                        while(temp->troLeft != NULL){
                            extraTemp = temp;
                            temp = temp->troLeft;
                        }
                        current->troDi = temp->troDi;
                        current->troCode = temp->troCode;
                        current->troDes = temp->troDes;
                        current->troWho = temp->troWho;
                        current->troSale = temp->troSale;
                        current->troPie = temp->troPie;
                        if(temp->troRight == NULL){
                            extraTemp->troLeft = NULL;
                            delete temp;
                            return;
                        }
                        else if(temp->troRight != NULL){
                            extraTemp->troLeft = temp->troRight;
                            delete temp;
                            return;
                        }
                    }
                }
			}

        }

};


class philippiTree{

	public:
		class philippiNode{
		public:
			string phiDi;
			string phiCode;
			string phiDes;
			double phiWho;
			double phiSale;
			double phiPie;

			philippiNode *phiRight;
			philippiNode *phiLeft;

		}*phiRoot;

		philippiTree(){ phiRoot = NULL; }

		void addItemPhi(string pDi, string pCode, string pDes, double pWho, double pSale, int pPie){
			philippiNode *current;
			current = phiRoot;
			if(phiRoot == NULL){
				phiRoot = newNodePhi(pDi, pCode, pDes, pWho, pSale, pPie);
				return;
			}
			while(1){
				if(pCode < current->phiCode){
					if(current->phiLeft == NULL){
						current->phiLeft = newNodePhi(pDi, pCode, pDes, pWho, pSale, pPie);
						return;
					}
					else {
					current = current->phiLeft;
					}
				}
				if(pCode >= current->phiCode){
					if(current->phiRight == NULL){
						current->phiRight = newNodePhi(pDi, pCode, pDes, pWho, pSale, pPie);
						return;
					}
					else {
					current = current->phiRight;
					}
				}
			}
		}

		philippiNode *newNodePhi(string pDi, string pCode, string pDes, double pWho, double pSale, int pPie){
			philippiNode *neos;
			neos = new(nothrow) philippiNode;
			neos->phiDi = pDi;
			neos->phiCode = pCode;
			neos->phiDes = pDes;
			neos->phiWho = pWho;
			neos->phiSale = pSale;
			neos->phiPie = pPie;
			neos->phiRight = NULL;
			neos->phiLeft = NULL;
			return (neos);
		}

		void phiDisplay(philippiNode *pptr){
		    int length;
			stringstream ssWho;
			stringstream ssSale;
			string strWho;
			string strSale;
			if(pptr == NULL) return;
			else{
				phiDisplay(pptr->phiLeft);
				cout << "| ";
				cout << pptr->phiDi;
				for(length = 0; length < 16 - pptr->phiDi.size(); length++) cout << " ";
				cout << "| ";
				cout << pptr->phiCode;
				for(length = 0; length < 18 - pptr->phiCode.size(); length++) cout << " ";
				cout << "| ";
				cout << pptr->phiDes;
				for(length = 0; length < 20 - pptr->phiDes.size(); length++) cout << " ";
				cout << "| ";
				cout << pptr->phiWho;
				ssWho << pptr->phiWho;
				strWho = ssWho.str();
				for(length = 0; length < 24 - strWho.size(); length++) cout << " ";
				cout << "| ";
				cout << pptr->phiSale;
				ssSale << pptr->phiSale;
				strSale = ssSale.str();
				for(length = 0; length < 22 - strSale.size(); length++) cout << " ";
				cout << "| ";
				cout << pptr->phiPie;
				cout << "\n_______________________________________________________________________________________________________________________\n\n";
				phiDisplay(pptr->phiRight);
			}
		}

        void phiDisplayOne(string pCode, philippiNode *pptr){
                int length;
                stringstream ssWho;
                stringstream ssSale;
                string strWho;
                string strSale;
                if(pptr == NULL) return;
                else{
                phiDisplayOne(pCode, pptr->phiLeft);
                if(pCode == pptr->phiCode){
                    cout << "\n___________________________________________________________________________________________\n\n";
                    cout << "| ";
                    cout << pptr->phiDi;
                    for(length = 0; length < 16 - pptr->phiDi.size(); length++) cout << " ";
                    cout << "| ";
                    cout << pptr->phiCode;
                    for(length = 0; length < 16 - pptr->phiCode.size(); length++) cout << " ";
                    cout << "| ";
                    cout << pptr->phiDes;
                    for(length = 0; length < 16 - pptr->phiDes.size(); length++) cout << " ";
                    cout << "| ";
                    cout << pptr->phiWho;
                    ssWho << pptr->phiWho;
                    strWho = ssWho.str();
                    for(length = 0; length < 10 - strWho.size(); length++) cout << " ";
                    cout << "| ";
                    cout << pptr->phiSale;
                    ssSale << pptr->phiSale;
                    strSale = ssSale.str();
                    for(length = 0; length < 10 - strSale.size(); length++) cout << " ";
                    cout << "| ";
                    cout << pptr->phiPie;
                    cout << "\n___________________________________________________________________________________________\n\n";
                }
                    phiDisplayOne(pCode, pptr->phiRight);

            }
        }

        void phiDisplayFile(philippiNode *pptr){
			if(pptr == NULL) return;
			else{
				phiFileDi << pptr->phiDi << endl;
				phiFileCode << pptr->phiCode << endl;
				phiFileDes << pptr->phiDes << endl;
				phiFilePr << pptr->phiWho << " " << pptr->phiSale << " " << pptr->phiPie << endl;
				phiDisplayFile(pptr->phiLeft);
				phiDisplayFile(pptr->phiRight);
			}
		}

		void savePhiData(){
			string lineDi;
			string lineCode;
			string lineDes;
			double fileWho;
			double fileSale;
			int filePie;

			ifstream phiDiFile;
			ifstream phiCodeFile;
			ifstream phiDesFile;
			ifstream phiPriceStockFile;

			phiDiFile.open("PHILIPPI_Di.txt");
			phiCodeFile.open("PHILIPPI_code.txt");
			phiDesFile.open("PHILIPPI_description.txt");
			phiPriceStockFile.open("PHILIPPI_price_stock.txt");

			while(!phiDiFile.eof() && !phiCodeFile.eof() && !phiDesFile.eof() && !phiPriceStockFile.eof()){
				getline(phiDiFile, lineDi);
				getline(phiCodeFile, lineCode);
				getline(phiDesFile, lineDes);
				phiPriceStockFile >> fileWho >> fileSale >> filePie;
				if(lineDi == "" || lineCode == "" || lineDes == "") continue;
				addItemPhi(lineDi, lineCode, lineDes, fileWho, fileSale, filePie);
			}

			phiDiFile.close();
			phiCodeFile.close();
			phiDesFile.close();
			phiPriceStockFile.close();


		}

        void changePhiPiece(string pCode, philippiNode *pptr, int newPiece){
            if(pptr == NULL) return;
            else{
                changePhiPiece(pCode, pptr->phiLeft, newPiece);
                if(pCode == pptr->phiCode){
                    pptr->phiPie = newPiece;
                }
                changePhiPiece(pCode, pptr->phiRight, newPiece);
            }
        }

        void findPhiCode(string pCode, philippiNode *pptr){
            if(pptr == NULL) return;
            else{
                findPhiCode(pCode, pptr->phiLeft);
                if(pCode == pptr->phiCode){
                    found = true;
                    return;
                }
                findPhiCode(pCode, pptr->phiRight);
            }
        }

        void toRestoreDisplay(philippiNode *pptr){
            if(pptr == NULL) return;
            else{
                toRestoreDisplay(pptr->phiLeft);
                if(pptr->phiPie < 2){
                    phiDisplayOne(pptr->phiCode, pptr);
                }
                toRestoreDisplay(pptr->phiRight);
            }
        }

        void phiDeleteNode(string pCode){
            philippiNode *current;
            philippiNode *preRight;
            philippiNode *preLeft;
            philippiNode *temp;
            philippiNode *extraTemp;
            current = phiRoot;
            while(1){
				if(pCode < current->phiCode){
				    preLeft = current;
				    preRight = NULL;
				    current = current->phiLeft;
				}
				else if(pCode > current->phiCode){
                    preRight = current;
                    preLeft = NULL;
                    current = current->phiRight;
				}
				else if(pCode == current->phiCode) break;
			}
			if(current->phiRight == NULL && current->phiLeft == NULL && current != phiRoot){
                if(preLeft == NULL){
                    preRight->phiRight = NULL;
                    delete current;
                    return;
                }
                else if(preRight == NULL){
                    preLeft->phiLeft = NULL;
                    delete current;
                    return;
                }
			}
			else if(current->phiRight == NULL && current->phiLeft != NULL && current != phiRoot){
                if(preLeft == NULL){
                    temp = current;
                    temp = temp->phiLeft;
                    preRight->phiRight = temp;
                    delete current;
                    return;
                }
                else if(preRight == NULL){
                    temp = current;
                    temp = temp->phiLeft;
                    preLeft->phiLeft = temp;
                    delete current;
                    return;
                }
			}
			else if(current->phiRight != NULL && current->phiLeft == NULL && current != phiRoot){
                if(preLeft == NULL){
                    temp = current;
                    temp = temp->phiRight;
                    preRight->phiRight = temp;
                    delete current;
                    return;
                }
                else if(preRight == NULL){
                    temp = current;
                    temp = temp->phiRight;
                    preLeft->phiLeft = temp;
                    delete current;
                    return;
                }
			}
			else if(current->phiRight != NULL && current->phiLeft != NULL && current != phiRoot){
                if(preLeft == NULL){
                    temp = current;
                    temp = temp->phiRight;
                    if(temp->phiLeft == NULL){
                        preRight->phiRight = temp;
                        temp->phiLeft = current->phiLeft;
                        delete current;
                        return;
                    }
                    else if(temp->phiLeft != NULL){
                        while(temp->phiLeft != NULL){
                            preRight = temp;
                            temp = temp->phiLeft;
                        }
                        current->phiDi = temp->phiDi;
                        current->phiCode = temp->phiCode;
                        current->phiDes = temp->phiDes;
                        current->phiWho = temp->phiWho;
                        current->phiSale = temp->phiSale;
                        current->phiPie = temp->phiPie;
                        if(temp->phiRight == NULL){
                            preRight->phiLeft = NULL;
                            delete temp;
                            return;
                        }
                        else if(temp->phiRight != NULL){
                            extraTemp = temp;
                            extraTemp = extraTemp->phiRight;
                            preRight->phiLeft = extraTemp;
                            delete temp;
                            return;
                        }
                    }
                }
                else if(preRight == NULL){
                    temp = current;
                    temp = temp->phiRight;
                    if(temp->phiLeft == NULL){
                        preLeft->phiLeft = temp;
                        temp->phiLeft = current->phiLeft;
                        delete current;
                        return;
                    }
                    else if(temp->phiLeft != NULL){
                        while(temp->phiLeft != NULL){
                            preLeft = temp;
                            temp = temp->phiLeft;
                        }
                        current->phiDi = temp->phiDi;
                        current->phiCode = temp->phiCode;
                        current->phiDes = temp->phiDes;
                        current->phiWho = temp->phiWho;
                        current->phiSale = temp->phiSale;
                        current->phiPie = temp->phiPie;
                        if(temp->phiRight == NULL){
                            preLeft->phiLeft = NULL;
                            delete temp;
                            return;
                        }
                        else if(temp->phiRight != NULL){
                            extraTemp = temp;
                            extraTemp = extraTemp->phiRight;
                            preLeft->phiLeft = extraTemp;
                            delete temp;
                            return;
                        }
                    }
                }
			}
			else if(current == phiRoot){
                temp = current;
                temp = current->phiRight;
                if(temp == NULL){
                    phiRoot = current->phiLeft;
                    delete current;
                    return;
                }
                else if(temp != NULL){
                    if(temp->phiLeft == NULL){
                        temp->phiLeft = current->phiLeft;
                        phiRoot = temp;
                        delete current;
                        return;
                    }
                    else if(temp->phiLeft != NULL){
                        while(temp->phiLeft != NULL){
                            extraTemp = temp;
                            temp = temp->phiLeft;
                        }
                        current->phiDi = temp->phiDi;
                        current->phiCode = temp->phiCode;
                        current->phiDes = temp->phiDes;
                        current->phiWho = temp->phiWho;
                        current->phiSale = temp->phiSale;
                        current->phiPie = temp->phiPie;
                        if(temp->phiRight == NULL){
                            extraTemp->phiLeft = NULL;
                            delete temp;
                            return;
                        }
                        else if(temp->phiRight != NULL){
                            extraTemp->phiLeft = temp->phiRight;
                            delete temp;
                            return;
                        }
                    }
                }
			}

        }

};


class artHartTree{

	public:
		class artHartNode{
		public:
			string artDi;
			string artCode;
			string artDes;
			double artWho;
			double artSale;
			double artPie;

			artHartNode *artRight;
			artHartNode *artLeft;

		}*artRoot;

		artHartTree(){ artRoot = NULL;	}


		void addItemArt(string aDi, string aCode, string aDes, double aWho, double aSale, int aPie){
			artHartNode *current;
			current = artRoot;
			if(artRoot == NULL){
				artRoot = newNodeArt(aDi, aCode, aDes, aWho, aSale, aPie);
				return;
			}
			while(1){
				if(aCode < current->artCode){
					if(current->artLeft == NULL){
						current->artLeft = newNodeArt(aDi, aCode, aDes, aWho, aSale, aPie);
						return;
					}
					else {
					current = current->artLeft;
					}
				}
				if(aCode >= current->artCode){
					if(current->artRight == NULL){
						current->artRight = newNodeArt(aDi, aCode, aDes, aWho, aSale, aPie);
						return;
					}
					else {
					current = current->artRight;
					}
				}
			}
		}


		artHartNode *newNodeArt(string aDi, string aCode, string aDes, double aWho, double aSale, int aPie){
			artHartNode *neos;
			neos = new(nothrow) artHartNode;
			neos->artDi = aDi;
			neos->artCode = aCode;
			neos->artDes = aDes;
			neos->artWho = aWho;
			neos->artSale = aSale;
			neos->artPie = aPie;
			neos->artRight = NULL;
			neos->artLeft = NULL;
			return (neos);
		}

		void artDisplay(artHartNode *aptr){
			int length;
			stringstream ssWho;
			stringstream ssSale;
			string strWho;
			string strSale;
			if(aptr == NULL) return;
			else{
				artDisplay(aptr->artLeft);
				cout << "| ";
				cout << aptr->artDi;
				for(length = 0; length < 16 - aptr->artDi.size(); length++) cout << " ";
				cout << "| ";
				cout << aptr->artCode;
				for(length = 0; length < 18 - aptr->artCode.size(); length++) cout << " ";
				cout << "| ";
				cout << aptr->artDes;
				for(length = 0; length < 20 - aptr->artDes.size(); length++) cout << " ";
				cout << "| ";
				cout << aptr->artWho;
				ssWho << aptr->artWho;
				strWho = ssWho.str();
				for(length = 0; length < 24 - strWho.size(); length++) cout << " ";
				cout << "| ";
				cout << aptr->artSale;
				ssSale << aptr->artSale;
				strSale = ssSale.str();
				for(length = 0; length < 22 - strSale.size(); length++) cout << " ";
				cout << "| ";
				cout << aptr->artPie;
				cout << "\n_______________________________________________________________________________________________________________________\n\n";
				artDisplay(aptr->artRight);
			}
		}

        void artDisplayOne(string aCode, artHartNode *aptr){
           int length;
			stringstream ssWho;
			stringstream ssSale;
			string strWho;
			string strSale;
			if(aptr == NULL) return;
			else{
				artDisplay(aptr->artLeft);
				if(aCode == aptr->artCode){
                    cout << "| ";
                    cout << aptr->artDi;
                    for(length = 0; length < 16 - aptr->artDi.size(); length++) cout << " ";
                    cout << "| ";
                    cout << aptr->artCode;
                    for(length = 0; length < 18 - aptr->artCode.size(); length++) cout << " ";
                    cout << "| ";
                    cout << aptr->artDes;
                    for(length = 0; length < 20 - aptr->artDes.size(); length++) cout << " ";
                    cout << "| ";
                    cout << aptr->artWho;
                    ssWho << aptr->artWho;
                    strWho = ssWho.str();
                    for(length = 0; length < 24 - strWho.size(); length++) cout << " ";
                    cout << "| ";
                    cout << aptr->artSale;
                    ssSale << aptr->artSale;
                    strSale = ssSale.str();
                    for(length = 0; length < 22 - strSale.size(); length++) cout << " ";
                    cout << "| ";
                    cout << aptr->artPie;
                    cout << "\n_______________________________________________________________________________________________________________________\n\n";
				}
				artDisplay(aptr->artRight);
			}
        }

        void artDisplayFile(artHartNode *aptr){
           if(aptr == NULL) return;
			else{
				artFileDi << aptr->artDi << endl;
				artFileCode << aptr->artCode << endl;
				artFileDes << aptr->artDes << endl;
				artFilePr << aptr->artWho << " " << aptr->artSale << " " << aptr->artPie << endl;
				artDisplayFile(aptr->artLeft);
				artDisplayFile(aptr->artRight);
			}
        }

		void saveArtData(){
			string lineDi;
			string lineCode;
			string lineDes;
			double fileWho;
			double fileSale;
			int filePie;

			ifstream artDiFile;
			ifstream artCodeFile;
			ifstream artDesFile;
			ifstream artPriceStockFile;

			artDiFile.open("ART_H_ART_Di.txt");
			artCodeFile.open("ART_H_ART_code.txt");
			artDesFile.open("ART_H_ART_description.txt");
			artPriceStockFile.open("ART_H_ART_price_stock.txt");

			while(!artDiFile.eof() && !artCodeFile.eof() && !artDesFile.eof() && !artPriceStockFile.eof()){
				getline(artDiFile, lineDi);
				getline(artCodeFile, lineCode);
				getline(artDesFile, lineDes);
				artPriceStockFile >> fileWho >> fileSale >> filePie;
				if(lineDi == "" || lineCode == "" || lineDes == "") continue;
				addItemArt(lineDi, lineCode, lineDes, fileWho, fileSale, filePie);
			}

			artDiFile.close();
			artCodeFile.close();
			artDesFile.close();
			artPriceStockFile.close();

		}

        void changeArtPiece(string aCode, artHartNode *aptr, int newPiece){
            if(aptr == NULL) return;
            else{
                changeArtPiece(aCode, aptr->artLeft, newPiece);
                if(aCode == aptr->artCode){
                    aptr->artPie = newPiece;
                }
                changeArtPiece(aCode, aptr->artRight, newPiece);
            }
        }

        void findArtCode(string aCode, artHartNode *aptr){
            if(aptr == NULL) return;
            else{
                findArtCode(aCode, aptr->artLeft);
                if(aCode == aptr->artCode){
                    found = true;
                    return;
                }
                findArtCode(aCode, aptr->artRight);
            }
        }

        void toRestoreDisplay(artHartNode *aptr){
            if(aptr == NULL) return;
            else{
                toRestoreDisplay(aptr->artLeft);
                if(aptr->artPie < 2){
                    artDisplayOne(aptr->artCode, aptr);
                }
                toRestoreDisplay(aptr->artRight);
            }
        }

        void artDeleteNode(string aCode){
            artHartNode *current;
            artHartNode *preRight;
            artHartNode *preLeft;
            artHartNode *temp;
            artHartNode *extraTemp;
            current = artRoot;
            while(1){
				if(aCode < current->artCode){
				    preLeft = current;
				    preRight = NULL;
				    current = current->artLeft;
				}
				else if(aCode > current->artCode){
                    preRight = current;
                    preLeft = NULL;
                    current = current->artRight;
				}
				else if(aCode == current->artCode) break;
			}
			if(current->artRight == NULL && current->artLeft == NULL && current != artRoot){
                if(preLeft == NULL){
                    preRight->artRight = NULL;
                    delete current;
                    return;
                }
                else if(preRight == NULL){
                    preLeft->artLeft = NULL;
                    delete current;
                    return;
                }
			}
			else if(current->artRight == NULL && current->artLeft != NULL && current != artRoot){
                if(preLeft == NULL){
                    temp = current;
                    temp = temp->artLeft;
                    preRight->artRight = temp;
                    delete current;
                    return;
                }
                else if(preRight == NULL){
                    temp = current;
                    temp = temp->artLeft;
                    preLeft->artLeft = temp;
                    delete current;
                    return;
                }
			}
			else if(current->artRight != NULL && current->artLeft == NULL  && current != artRoot){
                if(preLeft == NULL){
                    temp = current;
                    temp = temp->artRight;
                    preRight->artRight = temp;
                    delete current;
                    return;
                }
                else if(preRight == NULL){
                    temp = current;
                    temp = temp->artRight;
                    preLeft->artLeft = temp;
                    delete current;
                    return;
                }
			}
			else if(current->artRight != NULL && current->artLeft != NULL && current != artRoot){
                if(preLeft == NULL){
                    temp = current;
                    temp = temp->artRight;
                    if(temp->artLeft == NULL){
                        preRight->artRight = temp;
                        temp->artLeft = current->artLeft;
                        delete current;
                        return;
                    }
                    else if(temp->artLeft != NULL){
                        while(temp->artLeft != NULL){
                            preRight = temp;
                            temp = temp->artLeft;
                        }
                        current->artDi = temp->artDi;
                        current->artCode = temp->artCode;
                        current->artDes = temp->artDes;
                        current->artWho = temp->artWho;
                        current->artSale = temp->artSale;
                        current->artPie = temp->artPie;
                        if(temp->artRight == NULL){
                            preRight->artLeft = NULL;
                            delete temp;
                            return;
                        }
                        else if(temp->artRight != NULL){
                            extraTemp = temp;
                            extraTemp = extraTemp->artRight;
                            preRight->artLeft = extraTemp;
                            delete temp;
                            return;
                        }
                    }
                }
                else if(preRight == NULL){
                    temp = current;
                    temp = temp->artRight;
                    if(temp->artLeft == NULL){
                        preLeft->artLeft = temp;
                        temp->artLeft = current->artLeft;
                        delete current;
                        return;
                    }
                    else if(temp->artLeft != NULL){
                        while(temp->artLeft != NULL){
                            preLeft = temp;
                            temp = temp->artLeft;
                        }
                        current->artDi = temp->artDi;
                        current->artCode = temp->artCode;
                        current->artDes = temp->artDes;
                        current->artWho = temp->artWho;
                        current->artSale = temp->artSale;
                        current->artPie = temp->artPie;
                        if(temp->artRight == NULL){
                            preLeft->artLeft = NULL;
                            delete temp;
                            return;
                        }
                        else if(temp->artRight != NULL){
                            extraTemp = temp;
                            extraTemp = extraTemp->artRight;
                            preLeft->artLeft = extraTemp;
                            delete temp;
                            return;
                        }
                    }
                }
			}
			else if(current == artRoot){
                temp = current;
                temp = current->artRight;
                if(temp == NULL){
                    artRoot = current->artLeft;
                    delete current;
                    return;
                }
                else if(temp != NULL){
                    if(temp->artLeft == NULL){
                        temp->artLeft = current->artLeft;
                        artRoot = temp;
                        delete current;
                        return;
                    }
                    else if(temp->artLeft != NULL){
                        while(temp->artLeft != NULL){
                            extraTemp = temp;
                            temp = temp->artLeft;
                        }
                        current->artDi = temp->artDi;
                        current->artCode = temp->artCode;
                        current->artDes = temp->artDes;
                        current->artWho = temp->artWho;
                        current->artSale = temp->artSale;
                        current->artPie = temp->artPie;
                        if(temp->artRight == NULL){
                            extraTemp->artLeft = NULL;
                            delete temp;
                            return;
                        }
                        else if(temp->artRight != NULL){
                            extraTemp->artLeft = temp->artRight;
                            delete temp;
                            return;
                        }
                    }
                }
			}

        }

};


class epilektonTree{

	public:
		class epilektonNode{
		public:
			string epiDi;
			string epiCode;
			string epiDes;
			double epiWho;
			double epiSale;
			double epiPie;

			epilektonNode *epiRight;
			epilektonNode *epiLeft;

		}*epiRoot;

		epilektonTree(){ epiRoot = NULL; }

		void addItemEpi(string eDi, string eCode, string eDes, double eWho, double eSale, int ePie){
			epilektonNode *current;
			current = epiRoot;
			if(epiRoot == NULL){
				epiRoot = newNodeEpi(eDi, eCode, eDes, eWho, eSale, ePie);
				return;
			}
			while(1){
				if(eCode < current->epiCode){
					if(current->epiLeft == NULL){
						current->epiLeft = newNodeEpi(eDi, eCode, eDes, eWho, eSale, ePie);
						return;
					}
					else {
					current = current->epiLeft;
					}
				}
				if(eCode >= current->epiCode){
					if(current->epiRight == NULL){
						current->epiRight = newNodeEpi(eDi, eCode, eDes, eWho, eSale, ePie);
						return;
					}
					else {
					current = current->epiRight;
					}
				}
			}
		}

		epilektonNode *newNodeEpi(string eDi, string eCode, string eDes, double eWho, double eSale, int ePie){
			epilektonNode *neos;
			neos = new(nothrow) epilektonNode;
			neos->epiDi = eDi;
			neos->epiCode = eCode;
			neos->epiDes = eDes;
			neos->epiWho = eWho;
			neos->epiSale = eSale;
			neos->epiPie = ePie;
			neos->epiRight = NULL;
			neos->epiLeft = NULL;
			return (neos);
		}

		void epiDisplay(epilektonNode *eptr){
			int length;
			stringstream ssWho;
			stringstream ssSale;
			string strWho;
			string strSale;
			if(eptr == NULL) return;
			else{
				epiDisplay(eptr->epiLeft);
				cout << "| ";
				cout << eptr->epiDi;
				for(length = 0; length < 16 - eptr->epiDi.size(); length++) cout << " ";
				cout << "| ";
				cout << eptr->epiCode;
				for(length = 0; length < 18 - eptr->epiCode.size(); length++) cout << " ";
				cout << "| ";
				cout << eptr->epiDes;
				for(length = 0; length < 20 - eptr->epiDes.size(); length++) cout << " ";
				cout << "| ";
				cout << eptr->epiWho;
				ssWho << eptr->epiWho;
				strWho = ssWho.str();
				for(length = 0; length < 24 - strWho.size(); length++) cout << " ";
				cout << "| ";
				cout << eptr->epiSale;
				ssSale << eptr->epiSale;
				strSale = ssSale.str();
				for(length = 0; length < 22 - strSale.size(); length++) cout << " ";
				cout << "| ";
				cout << eptr->epiPie;
				cout << "\n_______________________________________________________________________________________________________________________\n\n";
				epiDisplay(eptr->epiRight);
			}
		}

        void epiDisplayOne(string eCode, epilektonNode *eptr){
            int length;
			stringstream ssWho;
			stringstream ssSale;
			string strWho;
			string strSale;
			if(eptr == NULL) return;
			else{
                epiDisplay(eptr->epiLeft);
                if(eCode == eptr->epiCode){
                    cout << "| ";
                    cout << eptr->epiDi;
                    for(length = 0; length < 16 - eptr->epiDi.size(); length++) cout << " ";
                    cout << "| ";
                    cout << eptr->epiCode;
                    for(length = 0; length < 18 - eptr->epiCode.size(); length++) cout << " ";
                    cout << "| ";
                    cout << eptr->epiDes;
                    for(length = 0; length < 20 - eptr->epiDes.size(); length++) cout << " ";
                    cout << "| ";
                    cout << eptr->epiWho;
                    ssWho << eptr->epiWho;
                    strWho = ssWho.str();
                    for(length = 0; length < 24 - strWho.size(); length++) cout << " ";
                    cout << "| ";
                    cout << eptr->epiSale;
                    ssSale << eptr->epiSale;
                    strSale = ssSale.str();
                    for(length = 0; length < 22 - strSale.size(); length++) cout << " ";
                    cout << "| ";
                    cout << eptr->epiPie;
                    cout << "\n_______________________________________________________________________________________________________________________\n\n";
                }
                epiDisplay(eptr->epiRight);
			}
        }

        void epiDisplayFile(epilektonNode *eptr){
			if(eptr == NULL) return;
			else{
				epiFileDi << eptr->epiDi << endl;
				epiFileCode << eptr->epiCode << endl;
				epiFileDes << eptr->epiDes << endl;
				epiFilePr << eptr->epiWho << " " << eptr->epiSale << " " << eptr->epiPie << endl;
				epiDisplayFile(eptr->epiLeft);
				epiDisplayFile(eptr->epiRight);
			}
		}

		void saveEpiData(){
			string lineDi;
			string lineCode;
			string lineDes;
			double fileWho;
			double fileSale;
			int filePie;

			ifstream epiDiFile;
			ifstream epiCodeFile;
			ifstream epiDesFile;
			ifstream epiPriceStockFile;

			epiDiFile.open("EPILEKTON_Di.txt");
			epiCodeFile.open("EPILEKTON_code.txt");
			epiDesFile.open("EPILEKTON_description.txt");
			epiPriceStockFile.open("EPILEKTON_price_stock.txt");

			while(!epiDiFile.eof() && !epiCodeFile.eof() && !epiDesFile.eof() && !epiPriceStockFile.eof()){
				getline(epiDiFile, lineDi);
				getline(epiCodeFile, lineCode);
				getline(epiDesFile, lineDes);
				epiPriceStockFile >> fileWho >> fileSale >> filePie;
				if(lineDi == "" || lineCode == "" || lineDes == "") continue;
				addItemEpi(lineDi, lineCode, lineDes, fileWho, fileSale, filePie);
			}

			epiDiFile.close();
			epiCodeFile.close();
			epiDesFile.close();
			epiPriceStockFile.close();


		}

        void changeEpiPiece(string eCode, epilektonNode *eptr, int newPiece){
            if(eptr == NULL) return;
            else{
                changeEpiPiece(eCode, eptr->epiLeft, newPiece);
                if(eCode == eptr->epiCode){
                    eptr->epiPie = newPiece;
                }
                changeEpiPiece(eCode, eptr->epiRight, newPiece);
            }
        }

        void findEpiCode(string eCode, epilektonNode *eptr){
            if(eptr == NULL) return;
            else{
                findEpiCode(eCode, eptr->epiLeft);
                if(eCode == eptr->epiCode){
                    found = true;
                    return;
                }
                findEpiCode(eCode, eptr->epiRight);
            }
        }

        void toRestoreDisplay(epilektonNode *eptr){
            if(eptr == NULL) return;
            else{
                toRestoreDisplay(eptr->epiLeft);
                if(eptr->epiPie < 2){
                    epiDisplayOne(eptr->epiCode, eptr);
                }
                toRestoreDisplay(eptr->epiRight);
            }
        }

        void epiDeleteNode(string eCode){
            epilektonNode *current;
            epilektonNode *preRight;
            epilektonNode *preLeft;
            epilektonNode *temp;
            epilektonNode *extraTemp;
            current = epiRoot;
            while(1){
				if(eCode < current->epiCode){
				    preLeft = current;
				    preRight = NULL;
				    current = current->epiLeft;
				}
				else if(eCode > current->epiCode){
                    preRight = current;
                    preLeft = NULL;
                    current = current->epiRight;
				}
				else if(eCode == current->epiCode) break;
			}
			if(current->epiRight == NULL && current->epiLeft == NULL  && current != epiRoot){
                if(preLeft == NULL){
                    preRight->epiRight = NULL;
                    delete current;
                    return;
                }
                else if(preRight == NULL){
                    preLeft->epiLeft = NULL;
                    delete current;
                    return;
                }
			}
			else if(current->epiRight == NULL && current->epiLeft != NULL  && current != epiRoot){
                if(preLeft == NULL){
                    temp = current;
                    temp = temp->epiLeft;
                    preRight->epiRight = temp;
                    delete current;
                    return;
                }
                else if(preRight == NULL){
                    temp = current;
                    temp = temp->epiLeft;
                    preLeft->epiLeft = temp;
                    delete current;
                    return;
                }
			}
			else if(current->epiRight != NULL && current->epiLeft == NULL  && current != epiRoot){
                if(preLeft == NULL){
                    temp = current;
                    temp = temp->epiRight;
                    preRight->epiRight = temp;
                    delete current;
                    return;
                }
                else if(preRight == NULL){
                    temp = current;
                    temp = temp->epiRight;
                    preLeft->epiLeft = temp;
                    delete current;
                    return;
                }
			}
			else if(current->epiRight != NULL && current->epiLeft != NULL && current != epiRoot){
                if(preLeft == NULL){
                    temp = current;
                    temp = temp->epiRight;
                    if(temp->epiLeft == NULL){
                        preRight->epiRight = temp;
                        temp->epiLeft = current->epiLeft;
                        delete current;
                        return;
                    }
                    else if(temp->epiLeft != NULL){
                        while(temp->epiLeft != NULL){
                            preRight = temp;
                            temp = temp->epiLeft;
                        }
                        current->epiDi = temp->epiDi;
                        current->epiCode = temp->epiCode;
                        current->epiDes = temp->epiDes;
                        current->epiWho = temp->epiWho;
                        current->epiSale = temp->epiSale;
                        current->epiPie = temp->epiPie;
                        if(temp->epiRight == NULL){
                            preRight->epiLeft = NULL;
                            delete temp;
                            return;
                        }
                        else if(temp->epiRight != NULL){
                            extraTemp = temp;
                            extraTemp = extraTemp->epiRight;
                            preRight->epiLeft = extraTemp;
                            delete temp;
                            return;
                        }
                    }
                }
                else if(preRight == NULL){
                    temp = current;
                    temp = temp->epiRight;
                    if(temp->epiLeft == NULL){
                        preLeft->epiLeft = temp;
                        temp->epiLeft = current->epiLeft;
                        delete current;
                        return;
                    }
                    else if(temp->epiLeft != NULL){
                        while(temp->epiLeft != NULL){
                            preLeft = temp;
                            temp = temp->epiLeft;
                        }
                        current->epiDi = temp->epiDi;
                        current->epiCode = temp->epiCode;
                        current->epiDes = temp->epiDes;
                        current->epiWho = temp->epiWho;
                        current->epiSale = temp->epiSale;
                        current->epiPie = temp->epiPie;
                        if(temp->epiRight == NULL){
                            preLeft->epiLeft = NULL;
                            delete temp;
                            return;
                        }
                        else if(temp->epiRight != NULL){
                            extraTemp = temp;
                            extraTemp = extraTemp->epiRight;
                            preLeft->epiLeft = extraTemp;
                            delete temp;
                            return;
                        }
                    }
                }
			}
			else if(current == epiRoot){
                temp = current;
                temp = current->epiRight;
                if(temp == NULL){
                    epiRoot = current->epiLeft;
                    delete current;
                    return;
                }
                else if(temp != NULL){
                    if(temp->epiLeft == NULL){
                        temp->epiLeft = current->epiLeft;
                        epiRoot = temp;
                        delete current;
                        return;
                    }
                    else if(temp->epiLeft != NULL){
                        while(temp->epiLeft != NULL){
                            extraTemp = temp;
                            temp = temp->epiLeft;
                        }
                        current->epiDi = temp->epiDi;
                        current->epiCode = temp->epiCode;
                        current->epiDes = temp->epiDes;
                        current->epiWho = temp->epiWho;
                        current->epiSale = temp->epiSale;
                        current->epiPie = temp->epiPie;
                        if(temp->epiRight == NULL){
                            extraTemp->epiLeft = NULL;
                            delete temp;
                            return;
                        }
                        else if(temp->epiRight != NULL){
                            extraTemp->epiLeft = temp->epiRight;
                            delete temp;
                            return;
                        }
                    }
                }
			}

        }

};


class salamandrasTree{

	public:
		class salamandrasNode{
		public:
			string salDi;
			string salCode;
			string salDes;
			double salWho;
			double salSale;
			double salPie;

			salamandrasNode *salRight;
			salamandrasNode *salLeft;

		}*salRoot;

		salamandrasTree(){ salRoot = NULL;	}

		void addItemSal(string sDi, string sCode, string sDes, double sWho, double sSale, int sPie){
			salamandrasNode *current;
			current = salRoot;
			if(salRoot == NULL){
				salRoot = newNodeSal(sDi, sCode, sDes, sWho, sSale, sPie);
				return;
			}
			while(1){
				if(sCode < current->salCode){
					if(current->salLeft == NULL){
						current->salLeft = newNodeSal(sDi, sCode, sDes, sWho, sSale, sPie);
						return;
					}
					else {
					current = current->salLeft;
					}
				}
				if(sCode >= current->salCode){
					if(current->salRight == NULL){
						current->salRight = newNodeSal(sDi, sCode, sDes, sWho, sSale, sPie);
						return;
					}
					else {
					current = current->salRight;
					}
				}
			}
		}

		salamandrasNode *newNodeSal(string sDi, string sCode, string sDes, double sWho, double sSale, int sPie){
			salamandrasNode *neos;
			neos = new(nothrow) salamandrasNode;
			neos->salDi = sDi;
			neos->salCode = sCode;
			neos->salDes = sDes;
			neos->salWho = sWho;
			neos->salSale = sSale;
			neos->salPie = sPie;
			neos->salRight = NULL;
			neos->salLeft = NULL;
			return (neos);
		}

		void salDisplay(salamandrasNode *sptr){
			int length;
			stringstream ssWho;
			stringstream ssSale;
			string strWho;
			string strSale;
			if(sptr == NULL) return;
			else{
				salDisplay(sptr->salLeft);
				cout << "| ";
				cout << sptr->salDi;
				for(length = 0; length < 16 - sptr->salDi.size(); length++) cout << " ";
				cout << "| ";
				cout << sptr->salCode;
				for(length = 0; length < 18 - sptr->salCode.size(); length++) cout << " ";
				cout << "| ";
				cout << sptr->salDes;
				for(length = 0; length < 20 - sptr->salDes.size(); length++) cout << " ";
				cout << "| ";
				cout << sptr->salWho;
				ssWho << sptr->salWho;
				strWho = ssWho.str();
				for(length = 0; length < 24 - strWho.size(); length++) cout << " ";
				cout << "| ";
				cout << sptr->salSale;
				ssSale << sptr->salSale;
				strSale = ssSale.str();
				for(length = 0; length < 22 - strSale.size(); length++) cout << " ";
				cout << "| ";
				cout << sptr->salPie;
				cout << "\n_______________________________________________________________________________________________________________________\n\n";
				salDisplay(sptr->salRight);
			}
		}

        void salDisplayOne(string sCode, salamandrasNode *sptr){
                int length;
                stringstream ssWho;
                stringstream ssSale;
                string strWho;
                string strSale;
                if(sptr == NULL) return;
                else{
                salDisplayOne(sCode, sptr->salLeft);
                if(sCode == sptr->salCode){
                    cout << "\n___________________________________________________________________________________________\n\n";
                    cout << "| ";
                    cout << sptr->salDi;
                    for(length = 0; length < 16 - sptr->salDi.size(); length++) cout << " ";
                    cout << "| ";
                    cout << sptr->salCode;
                    for(length = 0; length < 16 - sptr->salCode.size(); length++) cout << " ";
                    cout << "| ";
                    cout << sptr->salDes;
                    for(length = 0; length < 16 - sptr->salDes.size(); length++) cout << " ";
                    cout << "| ";
                    cout << sptr->salWho;
                    ssWho << sptr->salWho;
                    strWho = ssWho.str();
                    for(length = 0; length < 10 - strWho.size(); length++) cout << " ";
                    cout << "| ";
                    cout << sptr->salSale;
                    ssSale << sptr->salSale;
                    strSale = ssSale.str();
                    for(length = 0; length < 10 - strSale.size(); length++) cout << " ";
                    cout << "| ";
                    cout << sptr->salPie;
                    cout << "\n___________________________________________________________________________________________\n\n";
                }
                    salDisplayOne(sCode, sptr->salRight);

            }
        }

        void salDisplayFile(salamandrasNode *sptr){
			if(sptr == NULL) return;
			else{

				salFileDi << sptr->salDi << endl;
				salFileCode << sptr->salCode << endl;
				salFileDes << sptr->salDes << endl;
				salFilePr << sptr->salWho << " " << sptr->salSale << " " << sptr->salPie << endl;
				salDisplayFile(sptr->salLeft);
				salDisplayFile(sptr->salRight);
			}
		}

		void saveSalData(){
			string lineDi;
			string lineCode;
			string lineDes;
			double fileWho;
			double fileSale;
			int filePie;

			ifstream salDiFile;
			ifstream salCodeFile;
			ifstream salDesFile;
			ifstream salPriceStockFile;

			salDiFile.open("SALAMANDRAS_Di.txt");
			salCodeFile.open("SALAMANDRAS_code.txt");
			salDesFile.open("SALAMANDRAS_description.txt");
			salPriceStockFile.open("SALAMANDRAS_price_stock.txt");

			while(!salDiFile.eof() && !salCodeFile.eof() && !salDesFile.eof() && !salPriceStockFile.eof()){
				getline(salDiFile, lineDi);
				getline(salCodeFile, lineCode);
				getline(salDesFile, lineDes);
				salPriceStockFile >> fileWho >> fileSale >> filePie;
				if(lineDi == "" || lineCode == "" || lineDes == "") continue;
				addItemSal(lineDi, lineCode, lineDes, fileWho, fileSale, filePie);
			}

			salDiFile.close();
			salCodeFile.close();
			salDesFile.close();
			salPriceStockFile.close();


		}

        void changeSalPiece(string sCode, salamandrasNode *sptr, int newPiece){
            if(sptr == NULL) return;
            else{
                changeSalPiece(sCode, sptr->salLeft, newPiece);
                if(sCode == sptr->salCode){
                    sptr->salPie = newPiece;
                }
                changeSalPiece(sCode, sptr->salRight, newPiece);
            }
        }

        void findSalCode(string sCode, salamandrasNode *sptr){
            if(sptr == NULL) return;
            else{
                findSalCode(sCode, sptr->salLeft);
                if(sCode == sptr->salCode){
                    found = true;
                    return;
                }
                findSalCode(sCode, sptr->salRight);
            }
        }

        void toRestoreDisplay(salamandrasNode *sptr){
            if(sptr == NULL) return;
            else{
                toRestoreDisplay(sptr->salLeft);
                if(sptr->salPie < 2){
                    salDisplayOne(sptr->salCode, sptr);
                }
                toRestoreDisplay(sptr->salRight);
            }
        }

        void salDeleteNode(string sCode){
            salamandrasNode *current;
            salamandrasNode *preRight;
            salamandrasNode *preLeft;
            salamandrasNode *temp;
            salamandrasNode *extraTemp;
            current = salRoot;
            while(1){
				if(sCode < current->salCode){
				    preLeft = current;
				    preRight = NULL;
				    current = current->salLeft;
				}
				else if(sCode > current->salCode){
                    preRight = current;
                    preLeft = NULL;
                    current = current->salRight;
				}
				else if(sCode == current->salCode) break;
			}
			if(current->salRight == NULL && current->salLeft == NULL  && current != salRoot){
                if(preLeft == NULL){
                    preRight->salRight = NULL;
                    delete current;
                    return;
                }
                else if(preRight == NULL){
                    preLeft->salLeft = NULL;
                    delete current;
                    return;
                }
			}
			else if(current->salRight == NULL && current->salLeft != NULL  && current != salRoot){
                if(preLeft == NULL){
                    temp = current;
                    temp = temp->salLeft;
                    preRight->salRight = temp;
                    delete current;
                    return;
                }
                else if(preRight == NULL){
                    temp = current;
                    temp = temp->salLeft;
                    preLeft->salLeft = temp;
                    delete current;
                    return;
                }
			}
			else if(current->salRight != NULL && current->salLeft == NULL  && current != salRoot){
                if(preLeft == NULL){
                    temp = current;
                    temp = temp->salRight;
                    preRight->salRight = temp;
                    delete current;
                    return;
                }
                else if(preRight == NULL){
                    temp = current;
                    temp = temp->salRight;
                    preLeft->salLeft = temp;
                    delete current;
                    return;
                }
			}
			else if(current->salRight != NULL && current->salLeft != NULL && current != salRoot){
                if(preLeft == NULL){
                    temp = current;
                    temp = temp->salRight;
                    if(temp->salLeft == NULL){
                        preRight->salRight = temp;
                        temp->salLeft = current->salLeft;
                        delete current;
                        return;
                    }
                    else if(temp->salLeft != NULL){
                        while(temp->salLeft != NULL){
                            preRight = temp;
                            temp = temp->salLeft;
                        }
                        current->salDi = temp->salDi;
                        current->salCode = temp->salCode;
                        current->salDes = temp->salDes;
                        current->salWho = temp->salWho;
                        current->salSale = temp->salSale;
                        current->salPie = temp->salPie;
                        if(temp->salRight == NULL){
                            preRight->salLeft = NULL;
                            delete temp;
                            return;
                        }
                        else if(temp->salRight != NULL){
                            extraTemp = temp;
                            extraTemp = extraTemp->salRight;
                            preRight->salLeft = extraTemp;
                            delete temp;
                            return;
                        }
                    }
                }
                else if(preRight == NULL){
                    temp = current;
                    temp = temp->salRight;
                    if(temp->salLeft == NULL){
                        preLeft->salLeft = temp;
                        temp->salLeft = current->salLeft;
                        delete current;
                        return;
                    }
                    else if(temp->salLeft != NULL){
                        while(temp->salLeft != NULL){
                            preLeft = temp;
                            temp = temp->salLeft;
                        }
                        current->salDi = temp->salDi;
                        current->salCode = temp->salCode;
                        current->salDes = temp->salDes;
                        current->salWho = temp->salWho;
                        current->salSale = temp->salSale;
                        current->salPie = temp->salPie;
                        if(temp->salRight == NULL){
                            preLeft->salLeft = NULL;
                            delete temp;
                            return;
                        }
                        else if(temp->salRight != NULL){
                            extraTemp = temp;
                            extraTemp = extraTemp->salRight;
                            preLeft->salLeft = extraTemp;
                            delete temp;
                            return;
                        }
                    }
                }
			}
			else if(current == salRoot){
                temp = current;
                temp = current->salRight;
                if(temp == NULL){
                    salRoot = current->salLeft;
                    delete current;
                    return;
                }
                else if(temp != NULL){
                    if(temp->salLeft == NULL){
                        temp->salLeft = current->salLeft;
                        salRoot = temp;
                        delete current;
                        return;
                    }
                    else if(temp->salLeft != NULL){
                        while(temp->salLeft != NULL){
                            extraTemp = temp;
                            temp = temp->salLeft;
                        }
                        current->salDi = temp->salDi;
                        current->salCode = temp->salCode;
                        current->salDes = temp->salDes;
                        current->salWho = temp->salWho;
                        current->salSale = temp->salSale;
                        current->salPie = temp->salPie;
                        if(temp->salRight == NULL){
                            extraTemp->salLeft = NULL;
                            delete temp;
                            return;
                        }
                        else if(temp->salRight != NULL){
                            extraTemp->salLeft = temp->salRight;
                            delete temp;
                            return;
                        }
                    }
                }
			}

        }

};


class martDecoTree{

	public:
		class martDecoNode{
		public:
			string madeDi;
			string madeCode;
			string madeDes;
			double madeWho;
			double madeSale;
			double madePie;

			martDecoNode *madeRight;
			martDecoNode *madeLeft;

		}*madeRoot;

		martDecoTree(){ madeRoot = NULL; }

		void addItemMade(string mdDi, string mdCode, string mdDes, double mdWho, double mdSale, int mdPie){
			martDecoNode *current;
			current = madeRoot;
			if(madeRoot == NULL){
				madeRoot = newNodeMade(mdDi, mdCode, mdDes, mdWho, mdSale, mdPie);
				return;
			}
			while(1){
				if(mdCode < current->madeCode){
					if(current->madeLeft == NULL){
						current->madeLeft = newNodeMade(mdDi, mdCode, mdDes, mdWho, mdSale, mdPie);
						return;
					}
					else {
					current = current->madeLeft;
					}
				}
				if(mdCode >= current->madeCode){
					if(current->madeRight == NULL){
						current->madeRight = newNodeMade(mdDi, mdCode, mdDes, mdWho, mdSale, mdPie);
						return;
					}
					else {
					current = current->madeRight;
					}
				}
			}
		}

		martDecoNode *newNodeMade(string mdDi, string mdCode, string mdDes, double mdWho, double mdSale, int mdPie){
			martDecoNode *neos;
			neos = new(nothrow) martDecoNode;
			neos->madeDi = mdDi;
			neos->madeCode = mdCode;
			neos->madeDes = mdDes;
			neos->madeWho = mdWho;
			neos->madeSale = mdSale;
			neos->madePie = mdPie;
			neos->madeRight = NULL;
			neos->madeLeft = NULL;
			return (neos);
		}

		void madeDisplay(martDecoNode *mdptr){
			int length;
			stringstream ssWho;
			stringstream ssSale;
			string strWho;
			string strSale;
			if(mdptr == NULL) return;
			else{
				madeDisplay(mdptr->madeLeft);
				cout << "| ";
				cout << mdptr->madeDi;
				for(length = 0; length < 16 - mdptr->madeDi.size(); length++) cout << " ";
				cout << "| ";
				cout << mdptr->madeCode;
				for(length = 0; length < 18 - mdptr->madeCode.size(); length++) cout << " ";
				cout << "| ";
				cout << mdptr->madeDes;
				for(length = 0; length < 20 - mdptr->madeDes.size(); length++) cout << " ";
				cout << "| ";
				cout << mdptr->madeWho;
				ssWho << mdptr->madeWho;
				strWho = ssWho.str();
				for(length = 0; length < 24 - strWho.size(); length++) cout << " ";
				cout << "| ";
				cout << mdptr->madeSale;
				ssSale << mdptr->madeSale;
				strSale = ssSale.str();
				for(length = 0; length < 22 - strSale.size(); length++) cout << " ";
				cout << "| ";
				cout << mdptr->madePie;
				cout << "\n_______________________________________________________________________________________________________________________\n\n";
				madeDisplay(mdptr->madeRight);
			}
		}

        void madeDisplayOne(string mdCode, martDecoNode *mdptr){
                int length;
                stringstream ssWho;
                stringstream ssSale;
                string strWho;
                string strSale;
                if(mdptr == NULL) return;
                else{
                    madeDisplayOne(mdCode, mdptr->madeLeft);
                    if(mdptr->madeCode == mdCode){
                    cout << "| ";
                    cout << mdptr->madeDi;
                    for(length = 0; length < 16 - mdptr->madeDi.size(); length++) cout << " ";
                    cout << "| ";
                    cout << mdptr->madeCode;
                    for(length = 0; length < 18 - mdptr->madeCode.size(); length++) cout << " ";
                    cout << "| ";
                    cout << mdptr->madeDes;
                    for(length = 0; length < 20 - mdptr->madeDes.size(); length++) cout << " ";
                    cout << "| ";
                    cout << mdptr->madeWho;
                    ssWho << mdptr->madeWho;
                    strWho = ssWho.str();
                    for(length = 0; length < 24 - strWho.size(); length++) cout << " ";
                    cout << "| ";
                    cout << mdptr->madeSale;
                    ssSale << mdptr->madeSale;
                    strSale = ssSale.str();
                    for(length = 0; length < 22 - strSale.size(); length++) cout << " ";
                    cout << "| ";
                    cout << mdptr->madePie;
                    cout << "\n_______________________________________________________________________________________________________________________\n\n";
                    }
                    madeDisplayOne(mdCode, mdptr->madeRight);
                }
        }

        void madeDisplayFile(martDecoNode *mdptr){
			if(mdptr == NULL) return;
			else{

				madeFileDi << mdptr->madeDi << endl;
				madeFileCode << mdptr->madeCode << endl;
				madeFileDes << mdptr->madeDes << endl;
				madeFilePr << mdptr->madeWho << " " << mdptr->madeSale << " " << mdptr->madePie << endl;
				madeDisplayFile(mdptr->madeLeft);
				madeDisplayFile(mdptr->madeRight);
			}
		}

		void saveMadeData(){
			string lineDi;
			string lineCode;
			string lineDes;
			double fileWho;
			double fileSale;
			int filePie;

			ifstream madeDiFile;
			ifstream madeCodeFile;
			ifstream madeDesFile;
			ifstream madePriceStockFile;

			madeDiFile.open("MART_DECO_Di.txt");
			madeCodeFile.open("MART_DECO_code.txt");
			madeDesFile.open("MART_DECO_description.txt");
			madePriceStockFile.open("MART_DECO_price_stock.txt");

			while(!madeDiFile.eof() && !madeCodeFile.eof() && !madeDesFile.eof() && !madePriceStockFile.eof()){
				getline(madeDiFile, lineDi);
				getline(madeCodeFile, lineCode);
				getline(madeDesFile, lineDes);
				madePriceStockFile >> fileWho >> fileSale >> filePie;
				if(lineDi == "" || lineCode == "" || lineDes == "") continue;
				addItemMade(lineDi, lineCode, lineDes, fileWho, fileSale, filePie);
			}

			madeDiFile.close();
			madeCodeFile.close();
			madeDesFile.close();
			madePriceStockFile.close();


		}

        void changeMadePiece(string mdCode, martDecoNode *mdptr, int newPiece){
            if(mdptr == NULL) return;
            else{
                changeMadePiece(mdCode, mdptr->madeLeft, newPiece);
                if(mdCode == mdptr->madeCode){
                    mdptr->madePie = newPiece;
                }
                changeMadePiece(mdCode, mdptr->madeRight, newPiece);
            }
        }

        void findMadeCode(string mdCode, martDecoNode *mdptr){
            if(mdptr == NULL) return;
            else{
                findMadeCode(mdCode, mdptr->madeLeft);
                if(mdCode == mdptr->madeCode){
                    found = true;
                    return;
                }
                findMadeCode(mdCode, mdptr->madeRight);
            }
        }

        void toRestoreDisplay(martDecoNode *mdptr){
            if(mdptr == NULL) return;
            else{
                toRestoreDisplay(mdptr->madeLeft);
                if(mdptr->madePie < 2){
                    madeDisplayOne(mdptr->madeCode, mdptr);
                }
                toRestoreDisplay(mdptr->madeRight);
            }
        }

         void madeDeleteNode(string mdCode){
            martDecoNode *current;
            martDecoNode *preRight;
            martDecoNode *preLeft;
            martDecoNode *temp;
            martDecoNode *extraTemp;
            current = madeRoot;
            while(1){
				if(mdCode < current->madeCode){
				    preLeft = current;
				    preRight = NULL;
				    current = current->madeLeft;
				}
				else if(mdCode > current->madeCode){
                    preRight = current;
                    preLeft = NULL;
                    current = current->madeRight;
				}
				else if(mdCode == current->madeCode) break;
			}
			if(current->madeRight == NULL && current->madeLeft == NULL  && current != madeRoot){
                if(preLeft == NULL){
                    preRight->madeRight = NULL;
                    delete current;
                    return;
                }
                else if(preRight == NULL){
                    preLeft->madeLeft = NULL;
                    delete current;
                    return;
                }
			}
			else if(current->madeRight == NULL && current->madeLeft != NULL  && current != madeRoot){
                if(preLeft == NULL){
                    temp = current;
                    temp = temp->madeLeft;
                    preRight->madeRight = temp;
                    delete current;
                    return;
                }
                else if(preRight == NULL){
                    temp = current;
                    temp = temp->madeLeft;
                    preLeft->madeLeft = temp;
                    delete current;
                    return;
                }
			}
			else if(current->madeRight != NULL && current->madeLeft == NULL  && current != madeRoot){
                if(preLeft == NULL){
                    temp = current;
                    temp = temp->madeRight;
                    preRight->madeRight = temp;
                    delete current;
                    return;
                }
                else if(preRight == NULL){
                    temp = current;
                    temp = temp->madeRight;
                    preLeft->madeLeft = temp;
                    delete current;
                    return;
                }
			}
			else if(current->madeRight != NULL && current->madeLeft != NULL && current != madeRoot){
                if(preLeft == NULL){
                    temp = current;
                    temp = temp->madeRight;
                    if(temp->madeLeft == NULL){
                        preRight->madeRight = temp;
                        temp->madeLeft = current->madeLeft;
                        delete current;
                        return;
                    }
                    else if(temp->madeLeft != NULL){
                        while(temp->madeLeft != NULL){
                            preRight = temp;
                            temp = temp->madeLeft;
                        }
                        current->madeDi = temp->madeDi;
                        current->madeCode = temp->madeCode;
                        current->madeDes = temp->madeDes;
                        current->madeWho = temp->madeWho;
                        current->madeSale = temp->madeSale;
                        current->madePie = temp->madePie;
                        if(temp->madeRight == NULL){
                            preRight->madeLeft = NULL;
                            delete temp;
                            return;
                        }
                        else if(temp->madeRight != NULL){
                            extraTemp = temp;
                            extraTemp = extraTemp->madeRight;
                            preRight->madeLeft = extraTemp;
                            delete temp;
                            return;
                        }
                    }
                }
                else if(preRight == NULL){
                    temp = current;
                    temp = temp->madeRight;
                    if(temp->madeLeft == NULL){
                        preLeft->madeLeft = temp;
                        temp->madeLeft = current->madeLeft;
                        delete current;
                        return;
                    }
                    else if(temp->madeLeft != NULL){
                        while(temp->madeLeft != NULL){
                            preLeft = temp;
                            temp = temp->madeLeft;
                        }
                        current->madeDi = temp->madeDi;
                        current->madeCode = temp->madeCode;
                        current->madeDes = temp->madeDes;
                        current->madeWho = temp->madeWho;
                        current->madeSale = temp->madeSale;
                        current->madePie = temp->madePie;
                        if(temp->madeRight == NULL){
                            preLeft->madeLeft = NULL;
                            delete temp;
                            return;
                        }
                        else if(temp->madeRight != NULL){
                            extraTemp = temp;
                            extraTemp = extraTemp->madeRight;
                            preLeft->madeLeft = extraTemp;
                            delete temp;
                            return;
                        }
                    }
                }
			}
			else if(current == madeRoot){
                temp = current;
                temp = current->madeRight;
                if(temp == NULL){
                    madeRoot = current->madeLeft;
                    delete current;
                    return;
                }
                else if(temp != NULL){
                    if(temp->madeLeft == NULL){
                        temp->madeLeft = current->madeLeft;
                        madeRoot = temp;
                        delete current;
                        return;
                    }
                    else if(temp->madeLeft != NULL){
                        while(temp->madeLeft != NULL){
                            extraTemp = temp;
                            temp = temp->madeLeft;
                        }
                        current->madeDi = temp->madeDi;
                        current->madeCode = temp->madeCode;
                        current->madeDes = temp->madeDes;
                        current->madeWho = temp->madeWho;
                        current->madeSale = temp->madeSale;
                        current->madePie = temp->madePie;
                        if(temp->madeRight == NULL){
                            extraTemp->madeLeft = NULL;
                            delete temp;
                            return;
                        }
                        else if(temp->madeRight != NULL){
                            extraTemp->madeLeft = temp->madeRight;
                            delete temp;
                            return;
                        }
                    }
                }
			}

        }

};


class parkerTree{

	public:
		class parkerNode{
		public:
			string parDi;
			string parCode;
			string parDes;
			double parWho;
			double parSale;
			double parPie;

			parkerNode *parRight;
			parkerNode *parLeft;

		}*parRoot;

		parkerTree(){ parRoot = NULL; }

		void addItemPar(string pDi, string pCode, string pDes, double pWho, double pSale, int pPie){
			parkerNode *current;
			current = parRoot;
			if(parRoot == NULL){
				parRoot = newNodePar(pDi, pCode, pDes, pWho, pSale, pPie);
				return;
			}
			while(1){
				if(pCode < current->parCode){
					if(current->parLeft == NULL){
						current->parLeft = newNodePar(pDi, pCode, pDes, pWho, pSale, pPie);
						return;
					}
					else {
					current = current->parLeft;
					}
				}
				if(pCode >= current->parCode){
					if(current->parRight == NULL){
						current->parRight = newNodePar(pDi, pCode, pDes, pWho, pSale, pPie);
						return;
					}
					else {
					current = current->parRight;
					}
				}
			}
		}

		parkerNode *newNodePar(string pDi, string pCode, string pDes, double pWho, double pSale, int pPie){
			parkerNode *neos;
			neos = new(nothrow) parkerNode;
			neos->parDi = pDi;
			neos->parCode = pCode;
			neos->parDes = pDes;
			neos->parWho = pWho;
			neos->parSale = pSale;
			neos->parPie = pPie;
			neos->parRight = NULL;
			neos->parLeft = NULL;
			return (neos);
		}

		void parDisplay(parkerNode *pptr){
			int length;
			stringstream ssWho;
			stringstream ssSale;
			string strWho;
			string strSale;
			if(pptr == NULL) return;
			else{
				parDisplay(pptr->parLeft);
				cout << "| ";
				cout << pptr->parDi;
				for(length = 0; length < 16 - pptr->parDi.size(); length++) cout << " ";
				cout << "| ";
				cout << pptr->parCode;
				for(length = 0; length < 18 - pptr->parCode.size(); length++) cout << " ";
				cout << "| ";
				cout << pptr->parDes;
				for(length = 0; length < 20 - pptr->parDes.size(); length++) cout << " ";
				cout << "| ";
				cout << pptr->parWho;
				ssWho << pptr->parWho;
				strWho = ssWho.str();
				for(length = 0; length < 24 - strWho.size(); length++) cout << " ";
				cout << "| ";
				cout << pptr->parSale;
				ssSale << pptr->parSale;
				strSale = ssSale.str();
				for(length = 0; length < 22 - strSale.size(); length++) cout << " ";
				cout << "| ";
				cout << pptr->parPie;
				cout << "\n_______________________________________________________________________________________________________________________\n\n";
				parDisplay(pptr->parRight);
			}
		}

        void parDisplayOne(string pCode, parkerNode *pptr){
                int length;
                stringstream ssWho;
                stringstream ssSale;
                string strWho;
                string strSale;
                if(pptr == NULL) return;
                else{
                parDisplayOne(pCode, pptr->parLeft);
                if(pCode == pptr->parCode){
                    cout << "\n___________________________________________________________________________________________\n\n";
                    cout << "| ";
                    cout << pptr->parDi;
                    for(length = 0; length < 16 - pptr->parDi.size(); length++) cout << " ";
                    cout << "| ";
                    cout << pptr->parCode;
                    for(length = 0; length < 16 - pptr->parCode.size(); length++) cout << " ";
                    cout << "| ";
                    cout << pptr->parDes;
                    for(length = 0; length < 16 - pptr->parDes.size(); length++) cout << " ";
                    cout << "| ";
                    cout << pptr->parWho;
                    ssWho << pptr->parWho;
                    strWho = ssWho.str();
                    for(length = 0; length < 10 - strWho.size(); length++) cout << " ";
                    cout << "| ";
                    cout << pptr->parSale;
                    ssSale << pptr->parSale;
                    strSale = ssSale.str();
                    for(length = 0; length < 10 - strSale.size(); length++) cout << " ";
                    cout << "| ";
                    cout << pptr->parPie;
                    cout << "\n___________________________________________________________________________________________\n\n";
                }
                    parDisplayOne(pCode, pptr->parRight);

            }
        }

        void parDisplayFile(parkerNode *pptr){
			if(pptr == NULL) return;
			else{

				parFileDi << pptr->parDi << endl;
				parFileCode << pptr->parCode << endl;
				parFileDes << pptr->parDes << endl;
				parFilePr << pptr->parWho << " " << pptr->parSale << " " << pptr->parPie << endl;
				parDisplayFile(pptr->parLeft);
				parDisplayFile(pptr->parRight);
			}
		}

		void saveParData(){
			string lineDi;
			string lineCode;
			string lineDes;
			double fileWho;
			double fileSale;
			int filePie;

			ifstream parDiFile;
			ifstream parCodeFile;
			ifstream parDesFile;
			ifstream parPriceStockFile;

			parDiFile.open("PARKER_Di.txt");
			parCodeFile.open("PARKER_code.txt");
			parDesFile.open("PARKER_description.txt");
			parPriceStockFile.open("PARKER_price_stock.txt");

			while(!parDiFile.eof() && !parCodeFile.eof() && !parDesFile.eof() && !parPriceStockFile.eof()){
				getline(parDiFile, lineDi);
				getline(parCodeFile, lineCode);
				getline(parDesFile, lineDes);
				parPriceStockFile >> fileWho >> fileSale >> filePie;
				if(lineDi == "" || lineCode == "" || lineDes == "") continue;
				addItemPar(lineDi, lineCode, lineDes, fileWho, fileSale, filePie);
			}

			parDiFile.close();
			parCodeFile.close();
			parDesFile.close();
			parPriceStockFile.close();


		}

        void changeParPiece(string pCode, parkerNode *pptr, int newPiece){
            if(pptr == NULL) return;
            else{
                changeParPiece(pCode, pptr->parLeft, newPiece);
                if(pCode == pptr->parCode){
                    pptr->parPie = newPiece;
                }
                changeParPiece(pCode, pptr->parRight, newPiece);
            }
        }

        void findParCode(string pCode, parkerNode *pptr){
            if(pptr == NULL) return;
            else{
                findParCode(pCode, pptr->parLeft);
                if(pCode == pptr->parCode){
                    found = true;
                    return;
                }
                findParCode(pCode, pptr->parRight);
            }
        }

        void toRestoreDisplay(parkerNode *pptr){
            if(pptr == NULL) return;
            else{
                toRestoreDisplay(pptr->parLeft);
                if(pptr->parPie < 2){
                    parDisplayOne(pptr->parCode, pptr);
                }
                toRestoreDisplay(pptr->parRight);
            }
        }

        void parDeleteNode(string pCode){
            parkerNode *current;
            parkerNode *preRight;
            parkerNode *preLeft;
            parkerNode *temp;
            parkerNode *extraTemp;
            current = parRoot;
            while(1){
				if(pCode < current->parCode){
				    preLeft = current;
				    preRight = NULL;
				    current = current->parLeft;
				}
				else if(pCode > current->parCode){
                    preRight = current;
                    preLeft = NULL;
                    current = current->parRight;
				}
				else if(pCode == current->parCode) break;
			}
			if(current->parRight == NULL && current->parLeft == NULL  && current != parRoot){
                if(preLeft == NULL){
                    preRight->parRight = NULL;
                    delete current;
                    return;
                }
                else if(preRight == NULL){
                    preLeft->parLeft = NULL;
                    delete current;
                    return;
                }
			}
			else if(current->parRight == NULL && current->parLeft != NULL  && current != parRoot){
                if(preLeft == NULL){
                    temp = current;
                    temp = temp->parLeft;
                    preRight->parRight = temp;
                    delete current;
                    return;
                }
                else if(preRight == NULL){
                    temp = current;
                    temp = temp->parLeft;
                    preLeft->parLeft = temp;
                    delete current;
                    return;
                }
			}
			else if(current->parRight != NULL && current->parLeft == NULL  && current != parRoot){
                if(preLeft == NULL){
                    temp = current;
                    temp = temp->parRight;
                    preRight->parRight = temp;
                    delete current;
                    return;
                }
                else if(preRight == NULL){
                    temp = current;
                    temp = temp->parRight;
                    preLeft->parLeft = temp;
                    delete current;
                    return;
                }
			}
			else if(current->parRight != NULL && current->parLeft != NULL && current != parRoot){
                if(preLeft == NULL){
                    temp = current;
                    temp = temp->parRight;
                    if(temp->parLeft == NULL){
                        preRight->parRight = temp;
                        temp->parLeft = current->parLeft;
                        delete current;
                        return;
                    }
                    else if(temp->parLeft != NULL){
                        while(temp->parLeft != NULL){
                            preRight = temp;
                            temp = temp->parLeft;
                        }
                        current->parDi = temp->parDi;
                        current->parCode = temp->parCode;
                        current->parDes = temp->parDes;
                        current->parWho = temp->parWho;
                        current->parSale = temp->parSale;
                        current->parPie = temp->parPie;
                        if(temp->parRight == NULL){
                            preRight->parLeft = NULL;
                            delete temp;
                            return;
                        }
                        else if(temp->parRight != NULL){
                            extraTemp = temp;
                            extraTemp = extraTemp->parRight;
                            preRight->parLeft = extraTemp;
                            delete temp;
                            return;
                        }
                    }
                }
                else if(preRight == NULL){
                    temp = current;
                    temp = temp->parRight;
                    if(temp->parLeft == NULL){
                        preLeft->parLeft = temp;
                        temp->parLeft = current->parLeft;
                        delete current;
                        return;
                    }
                    else if(temp->parLeft != NULL){
                        while(temp->parLeft != NULL){
                            preLeft = temp;
                            temp = temp->parLeft;
                        }
                        current->parDi = temp->parDi;
                        current->parCode = temp->parCode;
                        current->parDes = temp->parDes;
                        current->parWho = temp->parWho;
                        current->parSale = temp->parSale;
                        current->parPie = temp->parPie;
                        if(temp->parRight == NULL){
                            preLeft->parLeft = NULL;
                            delete temp;
                            return;
                        }
                        else if(temp->parRight != NULL){
                            extraTemp = temp;
                            extraTemp = extraTemp->parRight;
                            preLeft->parLeft = extraTemp;
                            delete temp;
                            return;
                        }
                    }
                }
			}
			else if(current == parRoot){
                temp = current;
                temp = current->parRight;
                if(temp == NULL){
                    parRoot = current->parLeft;
                    delete current;
                    return;
                }
                else if(temp != NULL){
                    if(temp->parLeft == NULL){
                        temp->parLeft = current->parLeft;
                        parRoot = temp;
                        delete current;
                        return;
                    }
                    else if(temp->parLeft != NULL){
                        while(temp->parLeft != NULL){
                            extraTemp = temp;
                            temp = temp->parLeft;
                        }
                        current->parDi = temp->parDi;
                        current->parCode = temp->parCode;
                        current->parDes = temp->parDes;
                        current->parWho = temp->parWho;
                        current->parSale = temp->parSale;
                        current->parPie = temp->parPie;
                        if(temp->parRight == NULL){
                            extraTemp->parLeft = NULL;
                            delete temp;
                            return;
                        }
                        else if(temp->parRight != NULL){
                            extraTemp->parLeft = temp->parRight;
                            delete temp;
                            return;
                        }
                    }
                }
			}

        }

};




int main(){
	//Creating tree objects
	lexonTree lexon;
	troikaTree troika;
	philippiTree philippi;
	artHartTree artHart;
	epilektonTree epilekton;
	salamandrasTree salamandras;
	martDecoTree martDeco;
	parkerTree parker;
	//----------------------------

	//Choice Variables
	int choiceComp;
	int choiceLex;
	int choiceTro;
	int choicePhi;
	int choiceArt;
	int choiceEpi;
	int choiceSal;
	int choiceMade;
	int choicePar;
	//---------------------



	//Programm Needs
	bool goBack;
	bool backFromWho;
	bool fromChoice;
	int breakCount;
	char next;
	char beSure;
	char delOk;
    int blanks;
    string delCode;
	string tempDi;
	string tempCode;
	string tempDes;
	string pieCode;
	string yes;
	double tempWho;
	double tempSale;
	int tempPie;
	int newPie;
	int delLength;
	//----------------------

	//Saving data from files to trees (hopefully)
	lexon.saveLexData();
	troika.saveTroData();
	philippi.savePhiData();
	artHart.saveArtData();
	epilekton.saveEpiData();
	salamandras.saveSalData();
	martDeco.saveMadeData();
	parker.saveParData();
	//-------------------------------




	while(1){
    system("cls");
	cout << "\n*****************************Κυρίως Μενού******************************\n";
    cout << "|                                                                     |\n";
    cout << "|                                                                     |\n";
    cout << "|        Διάλεξε Εταιρία:                                             |\n";
    cout << "|                                                                     |\n";
    cout << "|        1.LEXON                                                      |\n";
    cout << "|        2.TROIKA                                                     |\n";
    cout << "|        3.PHILIPPI                                                   |\n";
    cout << "|        4.ART H ART                                                  |\n";
    cout << "|        5.ΕΠΙΛΕΚΤΟΝ                                                  |\n";
    cout << "|        6.ΣΑΛΑΜΑΝΔΡΑΣ                                                |\n";
    cout << "|        7.MART DECO                                                  |\n";
    cout << "|        8.PARKER                                                     |\n";
    cout << "|                                                                     |\n";
    cout << "| Για Έξοδο πατήστε 0                                                 |\n";
    cout << "|                                                                     |\n";
    cout << "***********************************************************************\n";
	cout << "****\n****Δώσε τον αντίστοιχο αριθμό από το μενού: ";
	cin >> 	choiceComp;
	while(choiceComp < 0 || choiceComp > 8 || cin.fail()){
		cin.clear();
		cin.ignore();
		cout << "****Μη αποδεκτός αριθμός. Παρακαλώ ξαναδοκιμάστε: ";
		cin >> choiceComp;
	}
	switch(choiceComp){
		case 1:
		    system("cls");
		    backFromWho = false;
			goBack = false;
			while(!goBack){
			cout << "\n**********************LEXON******LEXON******LEXON**********************\n";
			cout << "|                                                                     |\n";
    		cout << "|                                                                     |\n";
    		cout << "|        Διάλεξε Ενέργεια:                                            |\n";
   		 	cout << "|                                                                     |\n";
   		 	cout << "|        1.Δες όλα τα αποθέματα                                       |\n";
   		 	cout << "|        2.Πρόσθεσε ένα κωδικό                                        |\n";
    		cout << "|        3.Τροποποίησε ένα απόθεμα                                    |\n";
    		cout << "|        4.Δες τα αποθέματα που χρειάζονται ανανέωση                  |\n";
    		cout << "|        5.Διέγραψε έναν κωδικό                                       |\n";
    		cout << "|                                                                     |\n";
    		cout << "| Για επιστροφή στο Μενού πατήστε 0                                   |\n";
    		cout << "|                                                                     |\n";
    		cout << "**********************LEXON******LEXON******LEXON**********************\n";
    		cout << "****\n****Δώσε τον αντίστοιχο αριθμό από το μενού LEXON: ";
    		cin >> choiceLex;
    		while(choiceLex < 0 || choiceLex > 5 || cin.fail()){
				cin.clear();
				cin.ignore();
				cout << "****Μη αποδεκτός αριθμός. Παρακαλώ ξαναδοκιμάστε: ";
				cin >> choiceLex;
			}
			fromChoice = true;
			switch(choiceLex){
				case 1:
				    system("cls");
					if(lexon.lexRoot == NULL){
						cout << "\n\n****ΔΕΝ ΥΠΑΡΧΟΥΝ ΠΡΟΪΟΝΤΑ";
						while(true){
							cout << "\n****Πάτησε ENTER";
							cin.get(next);
							if(cin.get() == '\n') break;
						}
						system("cls");
						break;
					}
					else{
                        cout << "\n-----------------------------------------------------------------------------------------------------------------------";
                        cout << "\n\t\t\t\t\t\t   ΑΠΟΘΕΜΑΤΑ LEXON";
                        cout << "\n-----------------------------------------------------------------------------------------------------------------------\n";
                        cout << "\nΚωδικός Design In | Κωδικός Προϊόντος | Περιγραφή Προϊόντος | Χονδρική Τιμή με Φ.Π.Α. | Λιανική Τιμή με Φ.Π.Α | Τεμάχια";
						cout << "\n_______________________________________________________________________________________________________________________\n\n";
						lexon.lexDisplay(lexon.lexRoot);
						while(true){
							cout << "\n****Πάτησε ENTER";
							cin.get(next);
							if(cin.get() == '\n') break;
						}
						system("cls");
						break;
					}
				case 2:
				    system("cls");
					breakCount = 0;
					while(true){
                        found = false;
						if(fromChoice) cin.ignore(256, '\n');
						fromChoice = false;
						cout << "\n****Δώσε κωδικό προϊόντος_\t\t0.Πίσω\n";
						cout <<   "                         ";
						getline(cin, tempCode, '\n');
						lexon.findLexCode(tempCode, lexon.lexRoot);
						if(tempCode == "0") break;
                        else if(found){
                            cout << "\n****Ο κωσικός που εισάγατε υπάρχει ήδη.\n";
                            cout << "Πάτησε ENTER";
                            cin.get(beSure);
                            if(cin.get() == '\n'){
                                break;
                            }
                        }
						else breakCount++;
						while(true){
							cout << "\n****Δώσε κωδικό Design In_\t\t0.Πίσω\n";
							cout <<   "                         ";
							getline(cin, tempDi, '\n');
							if(tempDi == "0"){
								breakCount--;
								break;
							}
							else breakCount++;
							while(true){
								cout << "\n****Δώσε περιγραφή προϊόντος_\t\t0.Πίσω\n";
								cout <<   "                            ";
								if(backFromWho) cin.ignore(256, '\n');
								getline(cin, tempDes, '\n');
								backFromWho = false;
								if(tempDes == "0"){
									breakCount--;
									break;
								}
								else breakCount++;
								while(true){
									cout << "\n****Δώσε χονδρική τιμή πώλησης_\t\t0.Πίσω\n";
									cout <<   "                              ";
									cin >> tempWho;
									while(cin.fail()){
											cin.clear();
											cin.ignore();
											cout << "****Μη αποδεκτός αριθμός. Παρακαλώ ξαναδοκιμάστε: ";
											cin >> tempWho;
									}
									if(tempWho == 0){
                                        backFromWho = true;
										breakCount--;
										break;
									}
									else{
										tempSale = 2.5 * tempWho;
										breakCount++;
									}
									while(true){
										cout << "\n****Δώσε αριθμό τεμαχίων_\t\t0.Πίσω\n";
										cout <<   "                        ";
										cin >> tempPie;
										while(cin.fail()){
											cin.clear();
											cin.ignore();
											cout << "****Μη αποδεκτός αριθμός. Παρακαλώ ξαναδοκιμάστε: ";
											cin >> tempPie;
										}
										if(tempPie == 0){
											breakCount--;
											break;
										}
                                        else breakCount++;
										while(true){
                                            cout << "\n_______________________________________________________________________________________________________________________\n\n";
                                            cout << tempDi;
                                            for(blanks = 0; blanks < 18 - tempDi.size(); blanks++) cout << " ";
                                            cout << "| ";
                                            cout << tempCode;
                                            for(blanks = 0; blanks < 18 - tempCode.size(); blanks++) cout << " ";
                                            cout << "| ";
                                            cout << tempDes;
                                            for(blanks = 0; blanks < 20 - tempDes.size(); blanks++) cout << " ";
                                            cout << "| ";
                                            cout << tempWho;
                                            cout << "                   ";
                                            cout << "| ";
                                            cout << tempSale;
                                            cout << "                   ";
                                            cout << "| ";
                                            cout << tempPie;
                                            cout << "\n_______________________________________________________________________________________________________________________\n";
                                            cout << "\n\nΑν είσαι σίγουρος ότι θες να προσθέσεις το προϊόν με αυτά τα χαρακτηριστικα\n";
                                            cout << "πάτησε ENTER               0.Πίσω\n";
                                            cout << "            ";
                                            cin.get(beSure);
                                            if(cin.get() == '\n'){
                                                breakCount++;
                                                break;
                                            }
                                            else{
                                                breakCount--;
                                                break;
                                            }
                                            if(breakCount == 6) break;
										}
										if(breakCount == 6) break;
									}
									if(breakCount == 6) break;
							}
							if(breakCount == 6) break;
						}
						if(breakCount == 6) break;
					}
					if(breakCount == 6){
						lexon.addItemLex(tempDi, tempCode, tempDes, tempWho, tempSale, tempPie);
						lexFileDi.open("LEXON_Di.txt");
						lexFileCode.open("LEXON_code.txt");
						lexFileDes.open("LEXON_description.txt");
						lexFilePr.open("LEXON_price_stock.txt");
						lexon.lexDisplayFile(lexon.lexRoot);
						lexFileDi.close();
						lexFileCode.close();
						lexFileDes.close();
						lexFilePr.close();
						break;
					}
					}
					system("cls");
					break;
				case 3:
				    system("cls");
				    cin.ignore(256, '\n');
				    while(true){
                         //CAUTION
                        cout << "****\n****Δώσε τον κωδικο προϊόντος LEXON για τροποποίηση:_                  0.Πίσω\n";
                        cout <<       "                                                    ";
                        getline(cin, pieCode, '\n');
                        if(pieCode == "0") break;
                        else{
                            found == false;
                            lexon.findLexCode(pieCode, lexon.lexRoot);
                            while(!found){
                                cout << "\n****Ο κωδικός δεν βρέθηκε. Ξαναδοκιμάστε με καινούριο κωδικό:_                  0.Πίσω";
                                cout << "\n                                                             ";
                                getline(cin, pieCode, '\n');
                                lexon.findLexCode(pieCode, lexon.lexRoot);
                                if(pieCode == "0") break;
                            }
                            if(found){
                                lexon.lexDisplayOne(pieCode, lexon.lexRoot);
                                cout << "****Δώστε το νέο απόθεμα του προϊόντος με αυτά τα στοιχεία_\n";
                                cout << "                                                          ";
                                cin >> newPie;
                                while(cin.fail()){
                                    cin.clear();
                                    cin.ignore();
                                    cout << "\n****Μη αποδεκτός αριθμός. Παρακαλώ ξαναδοκιμάστε: ";
                                    cin >> newPie;
                                }
                                lexon.changeLexPiece(pieCode, lexon.lexRoot, newPie);
                                lexFileDi.open("LEXON_Di.txt");
                                lexFileCode.open("LEXON_code.txt");
                                lexFileDes.open("LEXON_description.txt");
                                lexFilePr.open("LEXON_price_stock.txt");
                                lexon.lexDisplayFile(lexon.lexRoot);
                                lexFileDi.close();
                                lexFileCode.close();
                                lexFileDes.close();
                                lexFilePr.close();
                                cout << "\n_____________________________________________\n";
                                cout << "****Τα νέα χαρακτηριστικά του προϊόντος είναι";
                                lexon.lexDisplayOne(pieCode, lexon.lexRoot);
                                while(true){
                                    cout << "\n****Για επιστροφή στο μενού της LEXON";
                                    cout << "\n****Πάτησε ENTER";
                                    cin.get(beSure);
                                    if(cin.get() == '\n') break;
                                }
                            }
                        }
                        break;
				    }
				    system("cls");
					break;
				case 4:
				    system("cls");
				    if(lexon.lexRoot == NULL){
						cout << "\n\n****ΔΕΝ ΥΠΑΡΧΟΥΝ ΠΡΟΪΟΝΤΑ";
						while(true){
							cout << "\n****Πάτησε ENTER";
							cin.get(next);
							if(cin.get() == '\n') break;
                        }
                        system("cls");
						break;
				    }
				    else{
				    cout << "\n****Αποθέματα LEXON που χρειάζονται ανανέωση\n";
				    lexon.toRestoreDisplay(lexon.lexRoot);
				    while(true){
                        cout << "\n****Πάτησε ENTER";
                        cin.get(next);
                        if(cin.get() == '\n') break;
                    }
                    system("cls");
                    break;
				    }
                case 5:
                    system("cls");
                    fromChoice = false;
                    while(1){
                    found = false;
                    cin.ignore(256, '\n');
                    cout << "\n****Δώσε κωδικό προϊόντος προς διαγραφή_\t0.Πίσω\n";
                    cout <<   "                                       ";
                    getline(cin, delCode, '\n');
                    if(delCode == "0") break;
                    lexon.findLexCode(delCode, lexon.lexRoot);
                    while(!found){
                        cout << "\n****Ο κωδικός δεν βρέθηκε. Ξαναδοκιμάστε με καινούριο κωδικό:_                  0.Πίσω";
                        cout << "\n                                                             ";
                        getline(cin, delCode, '\n');
                        lexon.findLexCode(delCode, lexon.lexRoot);
                        if(delCode == "0") break;
                    }
                    if(found){
                        cout << "\n****Αν είσαι σίγουρος ότι θες να διαγράψεις τον κωδικό " << delCode << " πληκτρολόγησε τη λέξη 'yes':___\t0.Πίσω";
                        cout << "\n                                                       ";
                        for(delLength = 0; delLength < delCode.size(); delLength++) cout << " ";
                        cout << "                             ";
                        cin >> yes;
                        if(yes != "yes") continue;
                        lexon.lexDeleteNode(delCode);
                        lexFileDi.open("LEXON_Di.txt");
                        lexFileCode.open("LEXON_code.txt");
                        lexFileDes.open("LEXON_description.txt");
                        lexFilePr.open("LEXON_price_stock.txt");
                        lexon.lexDisplayFile(lexon.lexRoot);
                        lexFileDi.close();
                        lexFileCode.close();
                        lexFileDes.close();
                        lexFilePr.close();
                        cout << "\n****\n****Ο κωδικός " << delCode << " διαγράφηκε.";
                        cout <<       "\n--------------";
                        for(delLength = 0; delLength < delCode.size(); delLength++) cout << "-";
                        cout << "------------";
                        while(true){
                            cout << "\n****Πάτησε ENTER";
                            cin.get(delOk);
                            if(cin.get() == '\n') break;
                        }

                    }
                    break;
                    }
                    system("cls");
                    break;
				case 0:
					goBack = true;
					break;
                    }
                }

			break;

		case 2:
		    system("cls");
		    backFromWho = false;
			goBack = false;
			while(!goBack){
			cout << "\n*******************TROIKA******TROIKA******TROIKA**********************\n";
			cout << "|                                                                     |\n";
    		cout << "|                                                                     |\n";
    		cout << "|        Διάλεξε Ενέργεια:                                            |\n";
   		 	cout << "|                                                                     |\n";
   		 	cout << "|        1.Δες όλα τα αποθέματα                                       |\n";
   		 	cout << "|        2.Πρόσθεσε ένα κωδικό                                        |\n";
    		cout << "|        3.Τροποποίησε ένα απόθεμα                                    |\n";
    		cout << "|        4.Δες τα αποθέματα που χρειάζονται ανανέωση                  |\n";
    		cout << "|        5.Διέγραψε έναν κωδικό                                       |\n";
    		cout << "|                                                                     |\n";
    		cout << "| Για επιστροφή στο Μενού πατήστε 0                                   |\n";
    		cout << "|                                                                     |\n";
    		cout << "*******************TROIKA******TROIKA******TROIKA**********************\n";
    		cout << "****Δώσε τον αντίστοιχο αριθμό: ";
    		cin >> choiceTro;
    		while(choiceTro < 0 || choiceTro > 5 || cin.fail()){
				cin.clear();
				cin.ignore();
				cout << "****Μη αποδεκτός αριθμός. Παρακαλώ ξαναδοκιμάστε: ";
				cin >> choiceTro;
			}
            fromChoice = true;
			switch(choiceTro){
				case 1:
				    system("cls");
					if(troika.troRoot == NULL){
						cout << "\n\n****ΔΕΝ ΥΠΑΡΧΟΥΝ ΠΡΟΪΟΝΤΑ TROIKA";
						while(true){
							cout << "\n****Πάτησε ENTER";
							cin.get(next);
							if(cin.get() == '\n') break;
						}
						system("cls");
						break;
					}
					else{
                        cout << "\n-----------------------------------------------------------------------------------------------------------------------";
                        cout << "\n\t\t\t\t\t\t   ΑΠΟΘΕΜΑΤΑ TROIKA";
                        cout << "\n-----------------------------------------------------------------------------------------------------------------------\n";
                        cout << "\nΚωδικός Design In | Κωδικός Προϊόντος | Περιγραφή Προϊόντος | Χονδρική Τιμή με Φ.Π.Α. | Λιανική Τιμή με Φ.Π.Α | Τεμάχια";
						cout << "\n_______________________________________________________________________________________________________________________\n\n";
						troika.troDisplay(troika.troRoot);
						while(true){
							cout << "\n****Πάτησε ENTER";
							cin.get(next);
							if(cin.get() == '\n') break;
						}
						system("cls");
						break;
					}
				case 2:
				    system("cls");
					breakCount = 0;
					while(true){
                        found = false;
						if(fromChoice) cin.ignore(256, '\n');
						fromChoice = false;
						cout << "\n****Δώσε κωδικό προϊόντος_\t\t0.Πίσω\n";
						cout <<   "                         ";
						getline(cin, tempCode, '\n');
						troika.findTroCode(tempCode, troika.troRoot);
						if(tempCode == "0") break;
                        else if(found){
                            cout << "\n****Ο κωσικός που εισάγατε υπάρχει ήδη.\n";
                            cout << "Πάτησε ENTER";
                            cin.get(beSure);
                            if(cin.get() == '\n'){
                                break;
                            }
                        }
						else breakCount++;
						while(true){
							cout << "\n****Δώσε κωδικό Design In_\t\t0.Πίσω\n";
							cout <<   "                         ";
							getline(cin, tempDi, '\n');
							if(tempDi == "0"){
								breakCount--;
								break;
							}
							else breakCount++;
							while(true){
								cout << "\n****Δώσε περιγραφή προϊόντος_\t\t0.Πίσω\n";
								cout <<   "                            ";
								if(backFromWho) cin.ignore(256, '\n');
								getline(cin, tempDes, '\n');
								backFromWho = false;
								if(tempDes == "0"){
									breakCount--;
									break;
								}
								else breakCount++;
								while(true){
									cout << "\n****Δώσε χονδρική τιμή πώλησης_\t\t0.Πίσω\n";
									cout <<   "                              ";
									cin >> tempWho;
									while(cin.fail()){
											cin.clear();
											cin.ignore();
											cout << "****Μη αποδεκτός αριθμός. Παρακαλώ ξαναδοκιμάστε: ";
											cin >> tempWho;
									}
									if(tempWho == 0){
                                        backFromWho = true;
										breakCount--;
										break;
									}
									else{
										tempSale = 2.5 * tempWho;
										breakCount++;
									}
									while(true){
										cout << "\n****Δώσε αριθμό τεμαχίων_\t\t0.Πίσω\n";
										cout <<   "                        ";
										cin >> tempPie;
										while(cin.fail()){
											cin.clear();
											cin.ignore();
											cout << "****Μη αποδεκτός αριθμός. Παρακαλώ ξαναδοκιμάστε: ";
											cin >> tempPie;
										}
										if(tempPie == 0){
											breakCount--;
											break;
										}
                                        else breakCount++;
										while(true){
                                            cout << "\n_______________________________________________________________________________________________________________________\n\n";
                                            cout << tempDi;
                                            for(blanks = 0; blanks < 18 - tempDi.size(); blanks++) cout << " ";
                                            cout << "| ";
                                            cout << tempCode;
                                            for(blanks = 0; blanks < 18 - tempCode.size(); blanks++) cout << " ";
                                            cout << "| ";
                                            cout << tempDes;
                                            for(blanks = 0; blanks < 20 - tempDes.size(); blanks++) cout << " ";
                                            cout << "| ";
                                            cout << tempWho;
                                            cout << "                   ";
                                            cout << "| ";
                                            cout << tempSale;
                                            cout << "                   ";
                                            cout << "| ";
                                            cout << tempPie;
                                            cout << "\n_______________________________________________________________________________________________________________________\n";
                                            cout << "\n\nΑν είσαι σίγουρος ότι θες να προσθέσεις το προϊόν με αυτά τα χαρακτηριστικα\n";
                                            cout << "πάτησε ENTER               0.Πίσω\n";
                                            cout << "            ";
                                            cin.get(beSure);
                                            if(cin.get() == '\n'){
                                                breakCount++;
                                                break;
                                            }
                                            else{
                                                breakCount--;
                                                break;
                                            }
                                            if(breakCount == 6) break;
										}
										if(breakCount == 6) break;
									}
									if(breakCount == 6) break;
							}
							if(breakCount == 6) break;
						}
						if(breakCount == 6) break;
					}
					if(breakCount == 6){
						troika.addItemTro(tempDi, tempCode, tempDes, tempWho, tempSale, tempPie);
						troFileDi.open("TROIKA_Di.txt");
						troFileCode.open("TROIKA_code.txt");
						troFileDes.open("TROIKA_description.txt");
						troFilePr.open("TROIKA_price_stock.txt");
						troika.troDisplayFile(troika.troRoot);
						troFileDi.close();
						troFileCode.close();
						troFileDes.close();
						troFilePr.close();
						break;
					}
					}
					system("cls");
					break;
				case 3:
				    system("cls");
				    cin.ignore(256, '\n');
				    while(true){
                         //CAUTION
                        cout << "****\n****Δώσε τον κωδικο προϊόντος LEXON για τροποποίηση:_                  0.Πίσω\n";
                        cout <<       "                                                    ";
                        getline(cin, pieCode, '\n');
                        if(pieCode == "0") break;
                        else{
                            found == false;
                            troika.findTroCode(pieCode, troika.troRoot);
                            while(!found){
                                cout << "\n****Ο κωδικός δεν βρέθηκε. Ξαναδοκιμάστε με καινούριο κωδικό:_                  0.Πίσω";
                                cout << "\n                                                             ";
                                getline(cin, pieCode, '\n');
                                if(pieCode == "0") break;
                            }
                            if(found){
                                troika.troDisplayOne(pieCode, troika.troRoot);
                                cout << "****Δώστε το νέο απόθεμα του προϊόντος με αυτά τα στοιχεία_\n";
                                cout << "                                                          ";
                                cin >> newPie;
                                while(cin.fail()){
                                    cin.clear();
                                    cin.ignore();
                                    cout << "\n****Μη αποδεκτός αριθμός. Παρακαλώ ξαναδοκιμάστε: ";
                                    cin >> newPie;
                                }
                                troika.changeTroPiece(pieCode, troika.troRoot, newPie);
                                troFileDi.open("TROIKA_Di.txt");
                                troFileCode.open("TROIKA_code.txt");
                                troFileDes.open("TROIKA_description.txt");
                                troFilePr.open("TROIKA_price_stock.txt");
                                troika.troDisplayFile(troika.troRoot);
                                troFileDi.close();
                                troFileCode.close();
                                troFileDes.close();
                                troFilePr.close();
                                cout << "\n_____________________________________________\n";
                                cout << "****Τα νέα χαρακτηριστικά του προϊόντος είναι";
                                troika.troDisplayOne(pieCode, troika.troRoot);
                                while(true){
                                    cout << "\n****Για επιστροφή στο μενού της TROIKA";
                                    cout << "\n****Πάτησε ENTER";
                                    cin.get(beSure);
                                    if(cin.get() == '\n') break;
                                }
                            }
                        }
                        break;
				    }
				    system("cls");
					break;
				case 4:
				    system("cls");
				    if(troika.troRoot == NULL){
						cout << "\n\n****ΔΕΝ ΥΠΑΡΧΟΥΝ ΠΡΟΪΟΝΤΑ";
						while(true){
							cout << "\n****Πάτησε ENTER";
							cin.get(next);
							if(cin.get() == '\n') break;
                        }
                        system("cls");
						break;
				    }
				    else{
				    cout << "\n****Αποθέματα TROIKA που χρειάζονται ανανέωση\n";
				    troika.toRestoreDisplay(troika.troRoot);
				    while(true){
							cout << "\n****Πάτησε ENTER";
							cin.get(next);
							if(cin.get() == '\n') break;
						}
						system("cls");
						break;
				    }
                case 5:
                    system("cls");
                    fromChoice = false;
                    while(1){
                    found = false;
                    cin.ignore(256, '\n');
                    cout << "\n****Δώσε κωδικό προϊόντος προς διαγραφή_\t0.Πίσω\n";
                    cout <<   "                                       ";
                    getline(cin, delCode, '\n');
                    if(delCode == "0") break;
                    troika.findTroCode(delCode, troika.troRoot);
                    while(!found){
                        cout << "\n****Ο κωδικός δεν βρέθηκε. Ξαναδοκιμάστε με καινούριο κωδικό:_                  0.Πίσω";
                        cout << "\n                                                             ";
                        getline(cin, delCode, '\n');
                        troika.findTroCode(delCode, troika.troRoot);
                        if(delCode == "0") break;
                    }
                    if(found){
                        cout << "\n****Αν είσαι σίγουρος ότι θες να διαγράψεις τον κωδικό " << delCode << " πληκτρολόγησε τη λέξη 'yes':___\t0.Πίσω";
                        cout << "\n                                                       ";
                        for(delLength = 0; delLength < delCode.size(); delLength++) cout << " ";
                        cout << "                             ";
                        cin >> yes;
                        if(yes != "yes") continue;
                        troika.troDeleteNode(delCode);
                        troFileDi.open("TROIKA_Di.txt");
                        troFileCode.open("TROIKA_code.txt");
                        troFileDes.open("TROIKA_description.txt");
                        troFilePr.open("TROIKA_price_stock.txt");
                        troika.troDisplayFile(troika.troRoot);
                        troFileDi.close();
                        troFileCode.close();
                        troFileDes.close();
                        troFilePr.close();
                        //troika.troDisplayFile(troika.troRoot);
                        cout << "\n****\n****Ο κωδικός " << delCode << " διαγράφηκε.";
                        cout <<       "\n--------------";
                        for(delLength = 0; delLength < delCode.size(); delLength++) cout << "-";
                        cout << "------------";
                        while(true){
                            cout << "\n****Πάτησε ENTER";
                            cin.get(delOk);
                            if(cin.get() == '\n') break;
                        }

                    }
                    break;
                    }
                    system("cls");
                    break;
				case 0:
					goBack = true;
					break;
                    }
			}
			break;



		case 3:
		    system("cls");
		    backFromWho = false;
			goBack = false;
			while(!goBack){
			cout << "\n*******************PHILIPPI****************PHILIPPI********************\n";
			cout << "|                                                                     |\n";
    		cout << "|                                                                     |\n";
   	 		cout << "|        Διάλεξε Ενέργεια:                                            |\n";
   			cout << "|                                                                     |\n";
   			cout << "|        1.Δες όλα τα αποθέματα                                       |\n";
	   	 	cout << "|        2.Πρόσθεσε ένα κωδικό                                        |\n";
	    	cout << "|        3.Τροποποίησε ένα απόθεμα                                    |\n";
    		cout << "|        4.Δες τα αποθέματα που χρειάζονται ανανέωση                  |\n";
    		cout << "|        5.Διέγραψε έναν κωδικό                                       |\n";
    		cout << "|                                                                     |\n";
    		cout << "| Για επιστροφή στο Μενού πατήστε 0                                   |\n";
    		cout << "|                                                                     |\n";
    		cout << "*******************PHILIPPI****************PHILIPPI********************\n";
    		cout << "****Δώσε τον αντίστοιχο αριθμό: ";
    		cin >> choicePhi;
    		while(choicePhi < 0 || choicePhi > 5 || cin.fail()){
				cin.clear();
				cin.ignore();
				cout << "****Μη αποδεκτός αριθμός. Παρακαλώ ξαναδοκιμάστε: ";
				cin >> choicePhi;
			}
			fromChoice = true;
			switch(choicePhi){
				case 1:
				    system("cls");
					if(philippi.phiRoot == NULL){
						cout << "\n\n****ΔΕΝ ΥΠΑΡΧΟΥΝ ΠΡΟΪΟΝΤΑ";
						while(true){
							cout << "\n****Πάτησε ENTER";
							cin.get(next);
							if(cin.get() == '\n') break;
						}
						system("cls");
						break;
					}
					else{
                        cout << "\n-----------------------------------------------------------------------------------------------------------------------";
                        cout << "\n\t\t\t\t\t\t   ΑΠΟΘΕΜΑΤΑ PHILIPPI";
                        cout << "\n-----------------------------------------------------------------------------------------------------------------------\n";
                        cout << "\nΚωδικός Design In | Κωδικός Προϊόντος | Περιγραφή Προϊόντος | Χονδρική Τιμή με Φ.Π.Α. | Λιανική Τιμή με Φ.Π.Α | Τεμάχια";
						cout << "\n_______________________________________________________________________________________________________________________\n\n";
						philippi.phiDisplay(philippi.phiRoot);
						while(true){
							cout << "\n****Πάτησε ENTER";
							cin.get(next);
							if(cin.get() == '\n') break;
						}
						system("cls");
						break;
					}
				case 2:
				    system("cls");
					breakCount = 0;
					while(true){
                        found = false;
						if(fromChoice) cin.ignore(256, '\n');
						fromChoice = false;
						cout << "\n****Δώσε κωδικό προϊόντος_\t\t0.Πίσω\n";
						cout <<   "                         ";
						getline(cin, tempCode, '\n');
						philippi.findPhiCode(tempCode, philippi.phiRoot);
						if(tempCode == "0") break;
                        else if(found){
                            cout << "\n****Ο κωσικός που εισάγατε υπάρχει ήδη.\n";
                            cout << "Πάτησε ENTER";
                            cin.get(beSure);
                            if(cin.get() == '\n'){
                                break;
                            }
                        }
						else breakCount++;
						while(true){
							cout << "\n****Δώσε κωδικό Design In_\t\t0.Πίσω\n";
							cout <<   "                         ";
							getline(cin, tempDi, '\n');
							if(tempDi == "0"){
								breakCount--;
								break;
							}
							else breakCount++;
							while(true){
								cout << "\n****Δώσε περιγραφή προϊόντος_\t\t0.Πίσω\n";
								cout <<   "                            ";
								if(backFromWho) cin.ignore(256, '\n');
								getline(cin, tempDes, '\n');
								backFromWho = false;
								if(tempDes == "0"){
									breakCount--;
									break;
								}
								else breakCount++;
								while(true){
									cout << "\n****Δώσε χονδρική τιμή πώλησης_\t\t0.Πίσω\n";
									cout <<   "                              ";
									cin >> tempWho;
									while(cin.fail()){
											cin.clear();
											cin.ignore();
											cout << "****Μη αποδεκτός αριθμός. Παρακαλώ ξαναδοκιμάστε: ";
											cin >> tempWho;
									}
									if(tempWho == 0){
                                        backFromWho = true;
										breakCount--;
										break;
									}
									else{
										tempSale = 2.5 * tempWho;
										breakCount++;
									}
									while(true){
										cout << "\n****Δώσε αριθμό τεμαχίων_\t\t0.Πίσω\n";
										cout <<   "                        ";
										cin >> tempPie;
										while(cin.fail()){
											cin.clear();
											cin.ignore();
											cout << "****Μη αποδεκτός αριθμός. Παρακαλώ ξαναδοκιμάστε: ";
											cin >> tempPie;
										}
										if(tempPie == 0){
											breakCount--;
											break;
										}
                                        else breakCount++;
										while(true){
                                            cout << "\n_______________________________________________________________________________________________________________________\n\n";
                                            cout << tempDi;
                                            for(blanks = 0; blanks < 18 - tempDi.size(); blanks++) cout << " ";
                                            cout << "| ";
                                            cout << tempCode;
                                            for(blanks = 0; blanks < 18 - tempCode.size(); blanks++) cout << " ";
                                            cout << "| ";
                                            cout << tempDes;
                                            for(blanks = 0; blanks < 20 - tempDes.size(); blanks++) cout << " ";
                                            cout << "| ";
                                            cout << tempWho;
                                            cout << "                   ";
                                            cout << "| ";
                                            cout << tempSale;
                                            cout << "                   ";
                                            cout << "| ";
                                            cout << tempPie;
                                            cout << "\n_______________________________________________________________________________________________________________________\n";
                                            cout << "\n\nΑν είσαι σίγουρος ότι θες να προσθέσεις το προϊόν με αυτά τα χαρακτηριστικα\n";
                                            cout << "πάτησε ENTER               0.Πίσω\n";
                                            cout << "            ";
                                            cin.get(beSure);
                                            if(cin.get() == '\n'){
                                                breakCount++;
                                                break;
                                            }
                                            else{
                                                breakCount--;
                                                break;
                                            }
                                            if(breakCount == 6) break;
										}
										if(breakCount == 6) break;
									}
									if(breakCount == 6) break;
							}
							if(breakCount == 6) break;
						}
						if(breakCount == 6) break;
					}
					if(breakCount == 6){
						philippi.addItemPhi(tempDi, tempCode, tempDes, tempWho, tempSale, tempPie);
						phiFileDi.open("PHILIPPI_Di.txt");
                        phiFileCode.open("PHILIPPI_code.txt");
                        phiFileDes.open("PHILIPPI_description.txt");
                        phiFilePr.open("PHILIPPI_price_stock.txt");
						philippi.phiDisplayFile(philippi.phiRoot);
						phiFileDi.close();
                        phiFileCode.close();
                        phiFileDes.close();
                        phiFilePr.close();
						break;
					}
					}
					system("cls");
					break;
				case 3:
				    system("cls");
				    cin.ignore(256, '\n');
				    while(true){
                         //CAUTION
                        cout << "****\n****Δώσε τον κωδικο προϊόντος PHILIPPI για τροποποίηση:_                  0.Πίσω\n";
                        cout <<       "                                                    ";
                        getline(cin, pieCode, '\n');
                        if(pieCode == "0") break;
                        else{
                            found == false;
                            philippi.findPhiCode(pieCode, philippi.phiRoot);
                            while(!found){
                                cout << "\n****Ο κωδικός δεν βρέθηκε. Ξαναδοκιμάστε με καινούριο κωδικό:_                  0.Πίσω";
                                cout << "\n                                                             ";
                                getline(cin, pieCode, '\n');
                                philippi.findPhiCode(pieCode, philippi.phiRoot);
                                if(pieCode == "0") break;
                            }
                            if(found){
                                philippi.phiDisplayOne(pieCode, philippi.phiRoot);
                                cout << "****Δώστε το νέο απόθεμα του προϊόντος με αυτά τα στοιχεία_\n";
                                cout << "                                                          ";
                                cin >> newPie;
                                while(cin.fail()){
                                    cin.clear();
                                    cin.ignore();
                                    cout << "\n****Μη αποδεκτός αριθμός. Παρακαλώ ξαναδοκιμάστε: ";
                                    cin >> newPie;
                                }
                                philippi.changePhiPiece(pieCode, philippi.phiRoot, newPie);
                                phiFileDi.open("PHILIPPI_Di.txt");
                                phiFileCode.open("PHILIPPI_code.txt");
                                phiFileDes.open("PHILIPPI_description.txt");
                                phiFilePr.open("PHILIPPI_price_stock.txt");
                                philippi.phiDisplayFile(philippi.phiRoot);
                                phiFileDi.close();
                                phiFileCode.close();
                                phiFileDes.close();
                                phiFilePr.close();
                                cout << "\n_____________________________________________\n";
                                cout << "****Τα νέα χαρακτηριστικά του προϊόντος είναι";
                                philippi.phiDisplayOne(pieCode, philippi.phiRoot);
                                while(true){
                                    cout << "\n****Για επιστροφή στο μενού της LEXON";
                                    cout << "\n****Πάτησε ENTER";
                                    cin.get(beSure);
                                    if(cin.get() == '\n') break;
                                }
                            }
                        }
                        break;
				    }
				    system("cls");
					break;
				case 4:
				    system("cls");
				    if(philippi.phiRoot == NULL){
						cout << "\n\n****ΔΕΝ ΥΠΑΡΧΟΥΝ ΠΡΟΪΟΝΤΑ";
						while(true){
							cout << "\n****Πάτησε ENTER";
							cin.get(next);
							if(cin.get() == '\n') break;
                        }
                        system("cls");
						break;
				    }
				    else{
				    cout << "\n****Αποθέματα PHILIPPI που χρειάζονται ανανέωση\n";
				    philippi.toRestoreDisplay(philippi.phiRoot);
				    while(true){
                        cout << "\n****Πάτησε ENTER";
                        cin.get(next);
                        if(cin.get() == '\n') break;
                    }
                    system("cls");
                    break;
				    }
                case 5:
                    system("cls");
                    fromChoice = false;
                    while(1){
                    found = false;
                    cin.ignore(256, '\n');
                    cout << "\n****Δώσε κωδικό προϊόντος προς διαγραφή_\t0.Πίσω\n";
                    cout <<   "                                       ";
                    getline(cin, delCode, '\n');
                    if(delCode == "0") break;
                    philippi.findPhiCode(delCode, philippi.phiRoot);
                    while(!found){
                        cout << "\n****Ο κωδικός δεν βρέθηκε. Ξαναδοκιμάστε με καινούριο κωδικό:_                  0.Πίσω";
                        cout << "\n                                                             ";
                        getline(cin, delCode, '\n');
                        philippi.findPhiCode(delCode, philippi.phiRoot);
                        if(delCode == "0") break;
                    }
                    if(found){
                        cout << "\n****Αν είσαι σίγουρος ότι θες να διαγράψεις τον κωδικό " << delCode << " πληκτρολόγησε τη λέξη 'yes':___\t0.Πίσω";
                        cout << "\n                                                       ";
                        for(delLength = 0; delLength < delCode.size(); delLength++) cout << " ";
                        cout << "                             ";
                        cin >> yes;
                        if(yes != "yes") continue;
                        philippi.phiDeleteNode(delCode);
                        phiFileDi.open("PHILIPPI_Di.txt");
                        phiFileCode.open("PHILIPPI_code.txt");
                        phiFileDes.open("PHILIPPI_description.txt");
                        phiFilePr.open("PHILIPPI_price_stock.txt");
						philippi.phiDisplayFile(philippi.phiRoot);
						phiFileDi.close();
                        phiFileCode.close();
                        phiFileDes.close();
                        phiFilePr.close();
                        //philippi.phiDisplayFile(philippi.phiRoot);
                        cout << "\n****\n****Ο κωδικός " << delCode << " διαγράφηκε.";
                        cout <<       "\n--------------";
                        for(delLength = 0; delLength < delCode.size(); delLength++) cout << "-";
                        cout << "------------";
                        while(true){
                            cout << "\n****Πάτησε ENTER";
                            cin.get(delOk);
                            if(cin.get() == '\n') break;
                        }

                    }
                    break;
                    }
                    system("cls");
                    break;
				case 0:
					goBack = true;
					break;
                    }
                }

			break;


		case 4:
		    system("cls");
		    backFromWho = false;
			goBack = false;
			while(!goBack){
			cout << "\n*******************ART*****ART*****ART*****ART*************************\n";
			cout << "|                                                                     |\n";
    		cout << "|                                                                     |\n";
   	 		cout << "|        Διάλεξε Ενέργεια:                                            |\n";
   			cout << "|                                                                     |\n";
   			cout << "|        1.Δες όλα τα αποθέματα                                       |\n";
	   	 	cout << "|        2.Πρόσθεσε ένα κωδικό                                        |\n";
	    	cout << "|        3.Τροποποίησε ένα απόθεμα                                    |\n";
    		cout << "|        4.Δες τα αποθέματα που χρειάζονται ανανέωση                  |\n";
    		cout << "|        5.Διέγραψε έναν κωδικό                                       |\n";
    		cout << "|                                                                     |\n";
    		cout << "| Για επιστροφή στο Μενού πατήστε 0                                   |\n";
    		cout << "|                                                                     |\n";
    		cout << "*******************ART*****ART*****ART*****ART*************************\n";
    		cout << "****Δώσε τον αντίστοιχο αριθμό: ";
    		cin >> choiceArt;
    		while(choiceArt < 0 || choiceArt > 5 || cin.fail()){
				cin.clear();
				cin.ignore();
				cout << "****Μη αποδεκτός αριθμός. Παρακαλώ ξαναδοκιμάστε: ";
				cin >> choiceArt;
			}
			fromChoice = true;
			switch(choiceArt){
				case 1:
				    system("cls");
					if(artHart.artRoot == NULL){
						cout << "\n\n****ΔΕΝ ΥΠΑΡΧΟΥΝ ΠΡΟΪΟΝΤΑ";
						while(true){
							cout << "\n****Πάτησε ENTER";
							cin.get(next);
							if(cin.get() == '\n') break;
						}
						system("cls");
						break;
					}
					else{
                        cout << "\n-----------------------------------------------------------------------------------------------------------------------";
                        cout << "\n\t\t\t\t\t\t   ΑΠΟΘΕΜΑΤΑ ART H ART";
                        cout << "\n-----------------------------------------------------------------------------------------------------------------------\n";
                        cout << "\nΚωδικός Design In | Κωδικός Προϊόντος | Περιγραφή Προϊόντος | Χονδρική Τιμή με Φ.Π.Α. | Λιανική Τιμή με Φ.Π.Α | Τεμάχια";
						cout << "\n_______________________________________________________________________________________________________________________\n\n";
						artHart.artDisplay(artHart.artRoot);
						while(true){
							cout << "\n****Πάτησε ENTER";
							cin.get(next);
							if(cin.get() == '\n') break;
						}
						system("cls");
						break;
					}
				case 2:
					breakCount = 0;
					while(true){
                        found = false;
						if(fromChoice) cin.ignore(256, '\n');
						fromChoice = false;
						cout << "\n****Δώσε κωδικό προϊόντος_\t\t0.Πίσω\n";
						cout <<   "                         ";
						getline(cin, tempCode, '\n');
						artHart.findArtCode(tempCode, artHart.artRoot);
						if(tempCode == "0") break;
                        else if(found){
                            cout << "\n****Ο κωσικός που εισάγατε υπάρχει ήδη.\n";
                            cout << "Πάτησε ENTER";
                            cin.get(beSure);
                            if(cin.get() == '\n'){
                                break;
                            }
                        }
						else breakCount++;
						while(true){
							cout << "\n****Δώσε κωδικό Design In_\t\t0.Πίσω\n";
							cout <<   "                         ";
							getline(cin, tempDi, '\n');
							if(tempDi == "0"){
								breakCount--;
								break;
							}
							else breakCount++;
							while(true){
								cout << "\n****Δώσε περιγραφή προϊόντος_\t\t0.Πίσω\n";
								cout <<   "                            ";
								if(backFromWho) cin.ignore(256, '\n');
								getline(cin, tempDes, '\n');
								backFromWho = false;
								if(tempDes == "0"){
									breakCount--;
									break;
								}
								else breakCount++;
								while(true){
									cout << "\n****Δώσε χονδρική τιμή πώλησης_\t\t0.Πίσω\n";
									cout <<   "                              ";
									cin >> tempWho;
									while(cin.fail()){
											cin.clear();
											cin.ignore();
											cout << "****Μη αποδεκτός αριθμός. Παρακαλώ ξαναδοκιμάστε: ";
											cin >> tempWho;
									}
									if(tempWho == 0){
                                        backFromWho = true;
										breakCount--;
										break;
									}
									else{
										tempSale = 2.5 * tempWho;
										breakCount++;
									}
									while(true){
										cout << "\n****Δώσε αριθμό τεμαχίων_\t\t0.Πίσω\n";
										cout <<   "                        ";
										cin >> tempPie;
										while(cin.fail()){
											cin.clear();
											cin.ignore();
											cout << "****Μη αποδεκτός αριθμός. Παρακαλώ ξαναδοκιμάστε: ";
											cin >> tempPie;
										}
										if(tempPie == 0){
											breakCount--;
											break;
										}
                                        else breakCount++;
										while(true){
                                            cout << "\n_______________________________________________________________________________________________________________________\n\n";
                                            cout << tempDi;
                                            for(blanks = 0; blanks < 18 - tempDi.size(); blanks++) cout << " ";
                                            cout << "| ";
                                            cout << tempCode;
                                            for(blanks = 0; blanks < 18 - tempCode.size(); blanks++) cout << " ";
                                            cout << "| ";
                                            cout << tempDes;
                                            for(blanks = 0; blanks < 20 - tempDes.size(); blanks++) cout << " ";
                                            cout << "| ";
                                            cout << tempWho;
                                            cout << "                   ";
                                            cout << "| ";
                                            cout << tempSale;
                                            cout << "                   ";
                                            cout << "| ";
                                            cout << tempPie;
                                            cout << "\n_______________________________________________________________________________________________________________________\n";
                                            cout << "\n\nΑν είσαι σίγουρος ότι θες να προσθέσεις το προϊόν με αυτά τα χαρακτηριστικα\n";
                                            cout << "πάτησε ENTER               0.Πίσω\n";
                                            cout << "            ";
                                            cin.get(beSure);
                                            if(cin.get() == '\n'){
                                                breakCount++;
                                                break;
                                            }
                                            else{
                                                breakCount--;
                                                break;
                                            }
                                            if(breakCount == 6) break;
										}
										if(breakCount == 6) break;
									}
									if(breakCount == 6) break;
							}
							if(breakCount == 6) break;
						}
						if(breakCount == 6) break;
					}
					if(breakCount == 6){
						artHart.addItemArt(tempDi, tempCode, tempDes, tempWho, tempSale, tempPie);
						artFileDi.open("ART_H_ART_Di.txt");
						artFileCode.open("ART_H_ART_code.txt");
						artFileDes.open("ART_H_ART_description.txt");
						artFilePr.open("ART_H_ART_price_stock.txt");
						artHart.artDisplayFile(artHart.artRoot);
						artFileDi.close();
						artFileCode.close();
						artFileDes.close();
						artFilePr.close();
						break;
					}
					}
					system("cls");
					break;
				case 3:
				    system("cls");
				    cin.ignore(256, '\n');
				    while(true){
                         //CAUTION
                        cout << "****\n****Δώσε τον κωδικο προϊόντος LEXON για τροποποίηση:_                  0.Πίσω\n";
                        cout <<       "                                                    ";
                        getline(cin, pieCode, '\n');
                        if(pieCode == "0") break;
                        else{
                            found == false;
                            artHart.findArtCode(pieCode, artHart.artRoot);
                            while(!found){
                                cout << "\n****Ο κωδικός δεν βρέθηκε. Ξαναδοκιμάστε με καινούριο κωδικό:_                  0.Πίσω";
                                cout << "\n                                                             ";
                                getline(cin, pieCode, '\n');
                                artHart.findArtCode(pieCode, artHart.artRoot);
                                if(pieCode == "0") break;
                            }
                            if(found){
                                artHart.artDisplayOne(pieCode, artHart.artRoot);
                                cout << "****Δώστε το νέο απόθεμα του προϊόντος με αυτά τα στοιχεία_\n";
                                cout << "                                                          ";
                                cin >> newPie;
                                while(cin.fail()){
                                    cin.clear();
                                    cin.ignore();
                                    cout << "\n****Μη αποδεκτός αριθμός. Παρακαλώ ξαναδοκιμάστε: ";
                                    cin >> newPie;
                                }
                                artHart.changeArtPiece(pieCode, artHart.artRoot, newPie);
                                artFileDi.open("ART_H_ART_Di.txt");
                                artFileCode.open("ART_H_ART_code.txt");
                                artFileDes.open("ART_H_ART_description.txt");
                                artFilePr.open("ART_H_ART_price_stock.txt");
                                artHart.artDisplayFile(artHart.artRoot);
                                artFileDi.close();
                                artFileCode.close();
                                artFileDes.close();
                                artFilePr.close();
                                cout << "\n_____________________________________________\n";
                                cout << "****Τα νέα χαρακτηριστικά του προϊόντος είναι";
                                artHart.artDisplayOne(pieCode, artHart.artRoot);
                                while(true){
                                    cout << "\n****Για επιστροφή στο μενού της ART H ART";
                                    cout << "\n****Πάτησε ENTER";
                                    cin.get(beSure);
                                    if(cin.get() == '\n') break;
                                }
                            }
                        }
                        break;
				    }
				    system("cls");
					break;
				case 4:
				    system("cls");
				    if(artHart.artRoot == NULL){
						cout << "\n\n****ΔΕΝ ΥΠΑΡΧΟΥΝ ΠΡΟΪΟΝΤΑ";
						while(true){
							cout << "\n****Πάτησε ENTER";
							cin.get(next);
							if(cin.get() == '\n') break;
                        }
                        system("cls");
						break;
				    }
				    else{
				    cout << "\n****Αποθέματα ART H ART που χρειάζονται ανανέωση\n";
				    artHart.toRestoreDisplay(artHart.artRoot);
				    while(true){
                        cout << "\n****Πάτησε ENTER";
                        cin.get(next);
                        if(cin.get() == '\n') break;
                    }
                    system("cls");
                    break;
				    }
                case 5:
                    system("cls");
                    fromChoice = false;
                    while(1){
                    found = false;
                    cin.ignore(256, '\n');
                    cout << "\n****Δώσε κωδικό προϊόντος προς διαγραφή_\t0.Πίσω\n";
                    cout <<   "                                       ";
                    getline(cin, delCode, '\n');
                    if(delCode == "0") break;
                    artHart.findArtCode(delCode, artHart.artRoot);
                    while(!found){
                        cout << "\n****Ο κωδικός δεν βρέθηκε. Ξαναδοκιμάστε με καινούριο κωδικό:_                  0.Πίσω";
                        cout << "\n                                                             ";
                        getline(cin, delCode, '\n');
                        artHart.findArtCode(delCode, artHart.artRoot);
                        if(delCode == "0") break;
                    }
                    if(found){
                        cout << "\n****Αν είσαι σίγουρος ότι θες να διαγράψεις τον κωδικό " << delCode << " πληκτρολόγησε τη λέξη 'yes':___\t0.Πίσω";
                        cout << "\n                                                       ";
                        for(delLength = 0; delLength < delCode.size(); delLength++) cout << " ";
                        cout << "                             ";
                        cin >> yes;
                        if(yes != "yes") continue;
                        artHart.artDeleteNode(delCode);
                        artFileDi.open("ART_H_ART_Di.txt");
						artFileCode.open("ART_H_ART_code.txt");
						artFileDes.open("ART_H_ART_description.txt");
						artFilePr.open("ART_H_ART_price_stock.txt");
						artHart.artDisplayFile(artHart.artRoot);
						artFileDi.close();
						artFileCode.close();
						artFileDes.close();
						artFilePr.close();
                        cout << "\n****\n****Ο κωδικός " << delCode << " διαγράφηκε.";
                        cout <<       "\n--------------";
                        for(delLength = 0; delLength < delCode.size(); delLength++) cout << "-";
                        cout << "------------";
                        while(true){
                            cout << "\n****Πάτησε ENTER";
                            cin.get(delOk);
                            if(cin.get() == '\n') break;
                        }

                    }
                    break;
                    }
                    system("cls");
                    break;
				case 0:
					goBack = true;
					break;
                    }
                }

            break;


		case 5:
		    system("cls");
		    backFromWho = false;
			goBack = false;
			while(!goBack){
			cout << "\n*******************ΕΠΙΛΕΚΤΟΝ***************ΕΠΙΛΕΚΤΟΝ*******************\n";
			cout << "|                                                                     |\n";
    		cout << "|                                                                     |\n";
   	 		cout << "|        Διάλεξε Ενέργεια:                                            |\n";
   			cout << "|                                                                     |\n";
   			cout << "|        1.Δες όλα τα αποθέματα                                       |\n";
	   	 	cout << "|        2.Πρόσθεσε ένα κωδικό                                        |\n";
	    	cout << "|        3.Τροποποίησε ένα απόθεμα                                    |\n";
    		cout << "|        4.Δες τα αποθέματα που χρειάζονται ανανέωση                  |\n";
    		cout << "|        5.Διέγραψε έναν κωδικό                                       |\n";
    		cout << "|                                                                     |\n";
    		cout << "| Για επιστροφή στο Μενού πατήστε 0                                   |\n";
    		cout << "|                                                                     |\n";
    		cout << "*******************ΕΠΙΛΕΚΤΟΝ***************ΕΠΙΛΕΚΤΟΝ*******************\n";
    		cout << "****Δώσε τον αντίστοιχο αριθμό: ";
    		cin >> choiceEpi;
    		while(choiceEpi < 0 || choiceEpi > 5 || cin.fail()){
				cin.clear();
				cin.ignore();
				cout << "****Μη αποδεκτός αριθμός. Παρακαλώ ξαναδοκιμάστε: ";
				cin >> choiceEpi;
			}
			fromChoice = true;
			switch(choiceEpi){
				case 1:
				    system("cls");
					if(epilekton.epiRoot == NULL){
						cout << "\n\n****ΔΕΝ ΥΠΑΡΧΟΥΝ ΠΡΟΪΟΝΤΑ";
						while(true){
							cout << "\n****Πάτησε ENTER";
							cin.get(next);
							if(cin.get() == '\n') break;
						}
						system("cls");
						break;
					}
					else{
                        cout << "\n-----------------------------------------------------------------------------------------------------------------------";
                        cout << "\n\t\t\t\t\t\t   ΑΠΟΘΕΜΑΤΑ ΕΠΙΛΕΚΤΟΝ";
                        cout << "\n-----------------------------------------------------------------------------------------------------------------------\n";
                        cout << "\nΚωδικός Design In | Κωδικός Προϊόντος | Περιγραφή Προϊόντος | Χονδρική Τιμή με Φ.Π.Α. | Λιανική Τιμή με Φ.Π.Α | Τεμάχια";
						cout << "\n_______________________________________________________________________________________________________________________\n\n";
						epilekton.epiDisplay(epilekton.epiRoot);
						while(true){
							cout << "\n****Πάτησε ENTER";
							cin.get(next);
							if(cin.get() == '\n') break;
						}
						system("cls");
						break;
					}
				case 2:
				    system("cls");
					breakCount = 0;
					while(true){
                        found = false;
						if(fromChoice) cin.ignore(256, '\n');
						fromChoice = false;
						cout << "\n****Δώσε κωδικό προϊόντος_\t\t0.Πίσω\n";
						cout <<   "                         ";
						getline(cin, tempCode, '\n');
						epilekton.findEpiCode(tempCode, epilekton.epiRoot);
						if(tempCode == "0") break;
                        else if(found){
                            cout << "\n****Ο κωσικός που εισάγατε υπάρχει ήδη.\n";
                            cout << "Πάτησε ENTER";
                            cin.get(beSure);
                            if(cin.get() == '\n'){
                                break;
                            }
                        }
						else breakCount++;
						while(true){
							cout << "\n****Δώσε κωδικό Design In_\t\t0.Πίσω\n";
							cout <<   "                         ";
							getline(cin, tempDi, '\n');
							if(tempDi == "0"){
								breakCount--;
								break;
							}
							else breakCount++;
							while(true){
								cout << "\n****Δώσε περιγραφή προϊόντος_\t\t0.Πίσω\n";
								cout <<   "                            ";
								if(backFromWho) cin.ignore(256, '\n');
								getline(cin, tempDes, '\n');
								backFromWho = false;
								if(tempDes == "0"){
									breakCount--;
									break;
								}
								else breakCount++;
								while(true){
									cout << "\n****Δώσε χονδρική τιμή πώλησης_\t\t0.Πίσω\n";
									cout <<   "                              ";
									cin >> tempWho;
									while(cin.fail()){
											cin.clear();
											cin.ignore();
											cout << "****Μη αποδεκτός αριθμός. Παρακαλώ ξαναδοκιμάστε: ";
											cin >> tempWho;
									}
									if(tempWho == 0){
                                        backFromWho = true;
										breakCount--;
										break;
									}
									else{
										tempSale = 2.5 * tempWho;
										breakCount++;
									}
									while(true){
										cout << "\n****Δώσε αριθμό τεμαχίων_\t\t0.Πίσω\n";
										cout <<   "                        ";
										cin >> tempPie;
										while(cin.fail()){
											cin.clear();
											cin.ignore();
											cout << "****Μη αποδεκτός αριθμός. Παρακαλώ ξαναδοκιμάστε: ";
											cin >> tempPie;
										}
										if(tempPie == 0){
											breakCount--;
											break;
										}
                                        else breakCount++;
										while(true){
                                            cout << "\n_______________________________________________________________________________________________________________________\n\n";
                                            cout << tempDi;
                                            for(blanks = 0; blanks < 18 - tempDi.size(); blanks++) cout << " ";
                                            cout << "| ";
                                            cout << tempCode;
                                            for(blanks = 0; blanks < 18 - tempCode.size(); blanks++) cout << " ";
                                            cout << "| ";
                                            cout << tempDes;
                                            for(blanks = 0; blanks < 20 - tempDes.size(); blanks++) cout << " ";
                                            cout << "| ";
                                            cout << tempWho;
                                            cout << "                   ";
                                            cout << "| ";
                                            cout << tempSale;
                                            cout << "                   ";
                                            cout << "| ";
                                            cout << tempPie;
                                            cout << "\n_______________________________________________________________________________________________________________________\n";
                                            cout << "\n\nΑν είσαι σίγουρος ότι θες να προσθέσεις το προϊόν με αυτά τα χαρακτηριστικα\n";
                                            cout << "πάτησε ENTER               0.Πίσω\n";
                                            cout << "            ";
                                            cin.get(beSure);
                                            if(cin.get() == '\n'){
                                                breakCount++;
                                                break;
                                            }
                                            else{
                                                breakCount--;
                                                break;
                                            }
                                            if(breakCount == 6) break;
										}
										if(breakCount == 6) break;
									}
									if(breakCount == 6) break;
							}
							if(breakCount == 6) break;
						}
						if(breakCount == 6) break;
					}
					if(breakCount == 6){
						epilekton.addItemEpi(tempDi, tempCode, tempDes, tempWho, tempSale, tempPie);
						epiFileDi.open("EPILEKTON_Di.txt");
						epiFileCode.open("EPILEKTON_code.txt");
						epiFileDes.open("EPILEKTON_description.txt");
						epiFilePr.open("EPILEKTON_price_stock.txt");
						epilekton.epiDisplayFile(epilekton.epiRoot);
						epiFileDi.close();
						epiFileCode.close();
						epiFileDes.close();
						epiFilePr.close();
						break;
					}
					}
					system("cls");
					break;
				case 3:
				    system("cls");
				    cin.ignore(256, '\n');
				    while(true){
                         //CAUTION
                        cout << "****\n****Δώσε τον κωδικο προϊόντος ΕΠΙΛΕΚΤΟΝ για τροποποίηση:_                  0.Πίσω\n";
                        cout <<       "                                                    ";
                        getline(cin, pieCode, '\n');
                        if(pieCode == "0") break;
                        else{
                            found == false;
                            epilekton.findEpiCode(pieCode, epilekton.epiRoot);
                            while(!found){
                                cout << "\n****Ο κωδικός δεν βρέθηκε. Ξαναδοκιμάστε με καινούριο κωδικό:_                  0.Πίσω";
                                cout << "\n                                                             ";
                                getline(cin, pieCode, '\n');
                                epilekton.findEpiCode(pieCode, epilekton.epiRoot);
                                if(pieCode == "0") break;
                            }
                            if(found){
                                epilekton.epiDisplayOne(pieCode, epilekton.epiRoot);
                                cout << "****Δώστε το νέο απόθεμα του προϊόντος με αυτά τα στοιχεία_\n";
                                cout << "                                                          ";
                                cin >> newPie;
                                while(cin.fail()){
                                    cin.clear();
                                    cin.ignore();
                                    cout << "\n****Μη αποδεκτός αριθμός. Παρακαλώ ξαναδοκιμάστε: ";
                                    cin >> newPie;
                                }
                                epilekton.changeEpiPiece(pieCode, epilekton.epiRoot, newPie);
                                epiFileDi.open("EPILEKTON_Di.txt");
                                epiFileCode.open("EPILEKTON_code.txt");
                                epiFileDes.open("EPILEKTON_description.txt");
                                epiFilePr.open("EPILEKTON_price_stock.txt");
                                epilekton.epiDisplayFile(epilekton.epiRoot);
                                epiFileDi.close();
                                epiFileCode.close();
                                epiFileDes.close();
                                epiFilePr.close();
                                cout << "\n_____________________________________________\n";
                                cout << "****Τα νέα χαρακτηριστικά του προϊόντος είναι";
                                epilekton.epiDisplayOne(pieCode, epilekton.epiRoot);
                                while(true){
                                    cout << "\n****Για επιστροφή στο μενού της ΕΠΙΛΕΚΤΟΝ";
                                    cout << "\n****Πάτησε ENTER";
                                    cin.get(beSure);
                                    if(cin.get() == '\n') break;
                                }
                            }
                        }
                        break;
				    }
				    system("cls");
					break;
				case 4:
				    system("cls");
				    if(epilekton.epiRoot == NULL){
						cout << "\n\n****ΔΕΝ ΥΠΑΡΧΟΥΝ ΠΡΟΪΟΝΤΑ";
						while(true){
							cout << "\n****Πάτησε ENTER";
							cin.get(next);
							if(cin.get() == '\n') break;
                        }
                        system("cls");
						break;
				    }
				    else{
				    cout << "\n****Αποθέματα LEXON που χρειάζονται ανανέωση\n";
				    epilekton.toRestoreDisplay(epilekton.epiRoot);
				    while(true){
                        cout << "\n****Πάτησε ENTER";
                        cin.get(next);
                        if(cin.get() == '\n') break;
                    }
                    system("cls");
                    break;
				    }
                case 5:
                    system("cls");
                    fromChoice = false;
                    while(1){
                    found = false;
                    cin.ignore(256, '\n');
                    cout << "\n****Δώσε κωδικό προϊόντος προς διαγραφή_\t0.Πίσω\n";
                    cout <<   "                                       ";
                    getline(cin, delCode, '\n');
                    if(delCode == "0") break;
                    epilekton.findEpiCode(delCode, epilekton.epiRoot);
                    while(!found){
                        cout << "\n****Ο κωδικός δεν βρέθηκε. Ξαναδοκιμάστε με καινούριο κωδικό:_                  0.Πίσω";
                        cout << "\n                                                             ";
                        getline(cin, delCode, '\n');
                        epilekton.findEpiCode(delCode, epilekton.epiRoot);
                        if(delCode == "0") break;
                    }
                    if(found){
                        cout << "\n****Αν είσαι σίγουρος ότι θες να διαγράψεις τον κωδικό " << delCode << " πληκτρολόγησε τη λέξη 'yes':___\t0.Πίσω";
                        cout << "\n                                                       ";
                        for(delLength = 0; delLength < delCode.size(); delLength++) cout << " ";
                        cout << "                             ";
                        cin >> yes;
                        if(yes != "yes") continue;
                        epilekton.epiDeleteNode(delCode);
                        epiFileDi.open("EPILEKTON_Di.txt");
						epiFileCode.open("EPILEKTON_code.txt");
						epiFileDes.open("EPILEKTON_description.txt");
						epiFilePr.open("EPILEKTON_price_stock.txt");
						epilekton.epiDisplayFile(epilekton.epiRoot);
						epiFileDi.close();
						epiFileCode.close();
						epiFileDes.close();
						epiFilePr.close();
                        cout << "\n****\n****Ο κωδικός " << delCode << " διαγράφηκε.";
                        cout <<       "\n--------------";
                        for(delLength = 0; delLength < delCode.size(); delLength++) cout << "-";
                        cout << "------------";
                        while(true){
                            cout << "\n****Πάτησε ENTER";
                            cin.get(delOk);
                            if(cin.get() == '\n') break;
                        }

                    }
                    break;
                    }
                    system("cls");
                    break;
				case 0:
					goBack = true;
					break;
                    }
                }

			break;


		case 6:
		    system("cls");
		    backFromWho = false;
			goBack = false;
			while(!goBack){
			cout << "\n*******************ΣΑΛΑΜΑΝΔΡΑΣ*************ΣΑΛΑΜΑΝΔΡΑΣ*****************\n";
			cout << "|                                                                     |\n";
    		cout << "|                                                                     |\n";
   	 		cout << "|        Διάλεξε Ενέργεια:                                            |\n";
   			cout << "|                                                                     |\n";
   			cout << "|        1.Δες όλα τα αποθέματα                                       |\n";
	   	 	cout << "|        2.Πρόσθεσε ένα κωδικό                                        |\n";
	    	cout << "|        3.Τροποποίησε ένα απόθεμα                                    |\n";
    		cout << "|        4.Δες τα αποθέματα που χρειάζονται ανανέωση                  |\n";
    		cout << "|        5.Διέγραψε έναν κωδικό                                       |\n";
    		cout << "|                                                                     |\n";
    		cout << "| Για επιστροφή στο Μενού πατήστε 0                                   |\n";
    		cout << "|                                                                     |\n";
    		cout << "*******************ΣΑΛΑΜΑΝΔΡΑΣ*************ΣΑΛΑΜΑΝΔΡΑΣ*****************\n";
    		cout << "****Δώσε τον αντίστοιχο αριθμό: ";
    		cin >> choiceSal;
    		while(choiceSal < 0 || choiceSal > 5 || cin.fail()){
				cin.clear();
				cin.ignore();
				cout << "****Μη αποδεκτός αριθμός. Παρακαλώ ξαναδοκιμάστε: ";
				cin >> choiceSal;
			}
			fromChoice = true;
			switch(choiceSal){
				case 1:
				    system("cls");
					if(salamandras.salRoot == NULL){
						cout << "\n\n****ΔΕΝ ΥΠΑΡΧΟΥΝ ΠΡΟΪΟΝΤΑ";
						while(true){
							cout << "\n****Πάτησε ENTER";
							cin.get(next);
							if(cin.get() == '\n') break;
						}
						system("cls");
						break;
					}
					else{
                        cout << "\n-----------------------------------------------------------------------------------------------------------------------";
                        cout << "\n\t\t\t\t\t\t   ΑΠΟΘΕΜΑΤΑ ΣΑΛΑΜΑΝΔΡΑΣ";
                        cout << "\n-----------------------------------------------------------------------------------------------------------------------\n";
                        cout << "\nΚωδικός Design In | Κωδικός Προϊόντος | Περιγραφή Προϊόντος | Χονδρική Τιμή με Φ.Π.Α. | Λιανική Τιμή με Φ.Π.Α | Τεμάχια";
						cout << "\n_______________________________________________________________________________________________________________________\n\n";
						salamandras.salDisplay(salamandras.salRoot);
						while(true){
							cout << "\n****Πάτησε ENTER";
							cin.get(next);
							if(cin.get() == '\n') break;
						}
						system("cls");
						break;
					}
				case 2:
				    system("cls");
					breakCount = 0;
					while(true){
                        found = false;
						if(fromChoice) cin.ignore(256, '\n');
						fromChoice = false;
						cout << "\n****Δώσε κωδικό προϊόντος_\t\t0.Πίσω\n";
						cout <<   "                         ";
						getline(cin, tempCode, '\n');
						salamandras.findSalCode(tempCode, salamandras.salRoot);
						if(tempCode == "0") break;
                        else if(found){
                            cout << "\n****Ο κωσικός που εισάγατε υπάρχει ήδη.\n";
                            cout << "Πάτησε ENTER";
                            cin.get(beSure);
                            if(cin.get() == '\n'){
                                break;
                            }
                        }
						else breakCount++;
						while(true){
							cout << "\n****Δώσε κωδικό Design In_\t\t0.Πίσω\n";
							cout <<   "                         ";
							getline(cin, tempDi, '\n');
							if(tempDi == "0"){
								breakCount--;
								break;
							}
							else breakCount++;
							while(true){
								cout << "\n****Δώσε περιγραφή προϊόντος_\t\t0.Πίσω\n";
								cout <<   "                            ";
								if(backFromWho) cin.ignore(256, '\n');
								getline(cin, tempDes, '\n');
								backFromWho = false;
								if(tempDes == "0"){
									breakCount--;
									break;
								}
								else breakCount++;
								while(true){
									cout << "\n****Δώσε χονδρική τιμή πώλησης_\t\t0.Πίσω\n";
									cout <<   "                              ";
									cin >> tempWho;
									while(cin.fail()){
											cin.clear();
											cin.ignore();
											cout << "****Μη αποδεκτός αριθμός. Παρακαλώ ξαναδοκιμάστε: ";
											cin >> tempWho;
									}
									if(tempWho == 0){
                                        backFromWho = true;
										breakCount--;
										break;
									}
									else{
										tempSale = 2.5 * tempWho;
										breakCount++;
									}
									while(true){
										cout << "\n****Δώσε αριθμό τεμαχίων_\t\t0.Πίσω\n";
										cout <<   "                        ";
										cin >> tempPie;
										while(cin.fail()){
											cin.clear();
											cin.ignore();
											cout << "****Μη αποδεκτός αριθμός. Παρακαλώ ξαναδοκιμάστε: ";
											cin >> tempPie;
										}
										if(tempPie == 0){
											breakCount--;
											break;
										}
                                        else breakCount++;
										while(true){
                                            cout << "\n_______________________________________________________________________________________________________________________\n\n";
                                            cout << tempDi;
                                            for(blanks = 0; blanks < 18 - tempDi.size(); blanks++) cout << " ";
                                            cout << "| ";
                                            cout << tempCode;
                                            for(blanks = 0; blanks < 18 - tempCode.size(); blanks++) cout << " ";
                                            cout << "| ";
                                            cout << tempDes;
                                            for(blanks = 0; blanks < 20 - tempDes.size(); blanks++) cout << " ";
                                            cout << "| ";
                                            cout << tempWho;
                                            cout << "                   ";
                                            cout << "| ";
                                            cout << tempSale;
                                            cout << "                   ";
                                            cout << "| ";
                                            cout << tempPie;
                                            cout << "\n_______________________________________________________________________________________________________________________\n";
                                            cout << "\n\nΑν είσαι σίγουρος ότι θες να προσθέσεις το προϊόν με αυτά τα χαρακτηριστικα\n";
                                            cout << "πάτησε ENTER               0.Πίσω\n";
                                            cout << "            ";
                                            cin.get(beSure);
                                            if(cin.get() == '\n'){
                                                breakCount++;
                                                break;
                                            }
                                            else{
                                                breakCount--;
                                                break;
                                            }
                                            if(breakCount == 6) break;
										}
										if(breakCount == 6) break;
									}
									if(breakCount == 6) break;
							}
							if(breakCount == 6) break;
						}
						if(breakCount == 6) break;
					}
					if(breakCount == 6){
						salamandras.addItemSal(tempDi, tempCode, tempDes, tempWho, tempSale, tempPie);
						salFileDi.open("SALAMANDRAS_Di.txt");
						salFileCode.open("SALAMANDRAS_code.txt");
						salFileDes.open("SALAMANDRAS_description.txt");
						salFilePr.open("SALAMANDRAS_price_stock.txt");
						salamandras.salDisplayFile(salamandras.salRoot);
						salFileDi.close();
						salFileCode.close();
						salFileDes.close();
						salFilePr.close();
						break;
					}
					}
					system("cls");
					break;
				case 3:
				    system("cls");
				    cin.ignore(256, '\n');
				    while(true){
                         //CAUTION
                        cout << "****\n****Δώσε τον κωδικο προϊόντος ΣΑΛΑΜΑΝΔΡΑΣ για τροποποίηση:_                  0.Πίσω\n";
                        cout <<       "                                                    ";
                        getline(cin, pieCode, '\n');
                        if(pieCode == "0") break;
                        else{
                            found == false;
                            salamandras.findSalCode(pieCode, salamandras.salRoot);
                            while(!found){
                                cout << "\n****Ο κωδικός δεν βρέθηκε. Ξαναδοκιμάστε με καινούριο κωδικό:_                  0.Πίσω";
                                cout << "\n                                                             ";
                                getline(cin, pieCode, '\n');
                                salamandras.findSalCode(pieCode, salamandras.salRoot);
                                if(pieCode == "0") break;
                            }
                            if(found){
                                salamandras.salDisplayOne(pieCode, salamandras.salRoot);
                                cout << "****Δώστε το νέο απόθεμα του προϊόντος με αυτά τα στοιχεία_\n";
                                cout << "                                                          ";
                                cin >> newPie;
                                while(cin.fail()){
                                    cin.clear();
                                    cin.ignore();
                                    cout << "\n****Μη αποδεκτός αριθμός. Παρακαλώ ξαναδοκιμάστε: ";
                                    cin >> newPie;
                                }
                                salamandras.changeSalPiece(pieCode, salamandras.salRoot, newPie);
                                salFileDi.open("SALAMANDRAS_Di.txt");
                                salFileCode.open("SALAMANDRAS_code.txt");
                                salFileDes.open("SALAMANDRAS_description.txt");
                                salFilePr.open("SALAMANDRAS_price_stock.txt");
                                salamandras.salDisplayFile(salamandras.salRoot);
                                salFileDi.close();
                                salFileCode.close();
                                salFileDes.close();
                                salFilePr.close();
                                cout << "\n_____________________________________________\n";
                                cout << "****Τα νέα χαρακτηριστικά του προϊόντος είναι";
                                salamandras.salDisplayOne(pieCode, salamandras.salRoot);
                                while(true){
                                    cout << "\n****Για επιστροφή στο μενού της ΣΑΛΑΜΑΝΔΡΑΣ";
                                    cout << "\n****Πάτησε ENTER";
                                    cin.get(beSure);
                                    if(cin.get() == '\n') break;
                                }
                            }
                        }
                        break;
				    }
				    system("cls");
					break;
				case 4:
				    system("cls");
				    if(salamandras.salRoot == NULL){
						cout << "\n\n****ΔΕΝ ΥΠΑΡΧΟΥΝ ΠΡΟΪΟΝΤΑ";
						while(true){
							cout << "\n****Πάτησε ENTER";
							cin.get(next);
							if(cin.get() == '\n') break;
                        }
                        system("cls");
						break;
				    }
				    else{
				    cout << "\n****Αποθέματα ΣΑΛΑΜΑΝΔΡΑΣ που χρειάζονται ανανέωση\n";
				    salamandras.toRestoreDisplay(salamandras.salRoot);
				    while(true){
                        cout << "\n****Πάτησε ENTER";
                        cin.get(next);
                        if(cin.get() == '\n') break;
                    }
                    system("cls");
                    break;
				    }
                case 5:
                    system("cls");
                    fromChoice = false;
                    while(1){
                    found = false;
                    cin.ignore(256, '\n');
                    cout << "\n****Δώσε κωδικό προϊόντος προς διαγραφή_\t0.Πίσω\n";
                    cout <<   "                                       ";
                    getline(cin, delCode, '\n');
                    if(delCode == "0") break;
                    salamandras.findSalCode(delCode, salamandras.salRoot);
                    while(!found){
                        cout << "\n****Ο κωδικός δεν βρέθηκε. Ξαναδοκιμάστε με καινούριο κωδικό:_                  0.Πίσω";
                        cout << "\n                                                             ";
                        getline(cin, delCode, '\n');
                        salamandras.findSalCode(delCode, salamandras.salRoot);
                        if(delCode == "0") break;
                    }
                    if(found){
                        cout << "\n****Αν είσαι σίγουρος ότι θες να διαγράψεις τον κωδικό " << delCode << " πληκτρολόγησε τη λέξη 'yes':___\t0.Πίσω";
                        cout << "\n                                                       ";
                        for(delLength = 0; delLength < delCode.size(); delLength++) cout << " ";
                        cout << "                             ";
                        cin >> yes;
                        if(yes != "yes") continue;
                        salamandras.salDeleteNode(delCode);
                        salFileDi.open("SALAMANDRAS_Di.txt");
						salFileCode.open("SALAMANDRAS_code.txt");
						salFileDes.open("SALAMANDRAS_description.txt");
						salFilePr.open("SALAMANDRAS_price_stock.txt");
						salamandras.salDisplayFile(salamandras.salRoot);
						salFileDi.close();
						salFileCode.close();
						salFileDes.close();
						salFilePr.close();
                        cout << "\n****\n****Ο κωδικός " << delCode << " διαγράφηκε.";
                        cout <<       "\n--------------";
                        for(delLength = 0; delLength < delCode.size(); delLength++) cout << "-";
                        cout << "------------";
                        while(true){
                            cout << "\n****Πάτησε ENTER";
                            cin.get(delOk);
                            if(cin.get() == '\n') break;
                        }

                    }
                    break;
                    }
                    system("cls");
                    break;
				case 0:
					goBack = true;
					break;
                    }
                }
            break;

		case 7:
		    system("cls");
		    backFromWho = false;
			goBack = false;
			while(!goBack){
			cout << "\n*******************MART*DECO***************MART*DECO*******************\n";
			cout << "|                                                                     |\n";
    		cout << "|                                                                     |\n";
   	 		cout << "|        Διάλεξε Ενέργεια:                                            |\n";
   			cout << "|                                                                     |\n";
   			cout << "|        1.Δες όλα τα αποθέματα                                       |\n";
	   	 	cout << "|        2.Πρόσθεσε ένα κωδικό                                        |\n";
	    	cout << "|        3.Τροποποίησε ένα απόθεμα                                    |\n";
    		cout << "|        4.Δες τα αποθέματα που χρειάζονται ανανέωση                  |\n";
    		cout << "|        5.Διέγραψε έναν κωδικό                                       |\n";
    		cout << "|                                                                     |\n";
    		cout << "| Για επιστροφή στο Μενού πατήστε 0                                   |\n";
    		cout << "|                                                                     |\n";
    		cout << "*******************MART*DECO***************MART*DECO*******************\n";
    		cout << "****Δώσε τον αντίστοιχο αριθμό: ";
    		cin >> choiceMade;
    		while(choiceMade < 0 || choiceMade > 5 || cin.fail()){
				cin.clear();
				cin.ignore();
				cout << "****Μη αποδεκτός αριθμός. Παρακαλώ ξαναδοκιμάστε: ";
				cin >> choiceMade;
			}
			fromChoice = true;
			switch(choiceMade){
				case 1:
				    system("cls");
					if(martDeco.madeRoot == NULL){
						cout << "\n\n****ΔΕΝ ΥΠΑΡΧΟΥΝ ΠΡΟΪΟΝΤΑ";
						while(true){
							cout << "\n****Πάτησε ENTER";
							cin.get(next);
							if(cin.get() == '\n') break;
						}
						system("cls");
						break;
					}
					else{
                        cout << "\n-----------------------------------------------------------------------------------------------------------------------";
                        cout << "\n\t\t\t\t\t\t   ΑΠΟΘΕΜΑΤΑ MART DECO";
                        cout << "\n-----------------------------------------------------------------------------------------------------------------------\n";
                        cout << "\nΚωδικός Design In | Κωδικός Προϊόντος | Περιγραφή Προϊόντος | Χονδρική Τιμή με Φ.Π.Α. | Λιανική Τιμή με Φ.Π.Α | Τεμάχια";
						cout << "\n_______________________________________________________________________________________________________________________\n\n";
						martDeco.madeDisplay(martDeco.madeRoot);
						while(true){
							cout << "\n****Πάτησε ENTER";
							cin.get(next);
							if(cin.get() == '\n') break;
						}
						system("cls");
						break;
					}
				case 2:
				    system("cls");
					breakCount = 0;
					while(true){
                        found = false;
						if(fromChoice) cin.ignore(256, '\n');
						fromChoice = false;
						cout << "\n****Δώσε κωδικό προϊόντος_\t\t0.Πίσω\n";
						cout <<   "                         ";
						getline(cin, tempCode, '\n');
						martDeco.findMadeCode(tempCode, martDeco.madeRoot);
						if(tempCode == "0") break;
                        else if(found){
                            cout << "\n****Ο κωσικός που εισάγατε υπάρχει ήδη.\n";
                            cout << "Πάτησε ENTER";
                            cin.get(beSure);
                            if(cin.get() == '\n'){
                                break;
                            }
                        }
						else breakCount++;
						while(true){
							cout << "\n****Δώσε κωδικό Design In_\t\t0.Πίσω\n";
							cout <<   "                         ";
							getline(cin, tempDi, '\n');
							if(tempDi == "0"){
								breakCount--;
								break;
							}
							else breakCount++;
							while(true){
								cout << "\n****Δώσε περιγραφή προϊόντος_\t\t0.Πίσω\n";
								cout <<   "                            ";
								if(backFromWho) cin.ignore(256, '\n');
								getline(cin, tempDes, '\n');
								backFromWho = false;
								if(tempDes == "0"){
									breakCount--;
									break;
								}
								else breakCount++;
								while(true){
									cout << "\n****Δώσε χονδρική τιμή πώλησης_\t\t0.Πίσω\n";
									cout <<   "                              ";
									cin >> tempWho;
									while(cin.fail()){
											cin.clear();
											cin.ignore();
											cout << "****Μη αποδεκτός αριθμός. Παρακαλώ ξαναδοκιμάστε: ";
											cin >> tempWho;
									}
									if(tempWho == 0){
                                        backFromWho = true;
										breakCount--;
										break;
									}
									else{
										tempSale = 2.5 * tempWho;
										breakCount++;
									}
									while(true){
										cout << "\n****Δώσε αριθμό τεμαχίων_\t\t0.Πίσω\n";
										cout <<   "                        ";
										cin >> tempPie;
										while(cin.fail()){
											cin.clear();
											cin.ignore();
											cout << "****Μη αποδεκτός αριθμός. Παρακαλώ ξαναδοκιμάστε: ";
											cin >> tempPie;
										}
										if(tempPie == 0){
											breakCount--;
											break;
										}
                                        else breakCount++;
										while(true){
                                            cout << "\n_______________________________________________________________________________________________________________________\n\n";
                                            cout << tempDi;
                                            for(blanks = 0; blanks < 18 - tempDi.size(); blanks++) cout << " ";
                                            cout << "| ";
                                            cout << tempCode;
                                            for(blanks = 0; blanks < 18 - tempCode.size(); blanks++) cout << " ";
                                            cout << "| ";
                                            cout << tempDes;
                                            for(blanks = 0; blanks < 20 - tempDes.size(); blanks++) cout << " ";
                                            cout << "| ";
                                            cout << tempWho;
                                            cout << "                   ";
                                            cout << "| ";
                                            cout << tempSale;
                                            cout << "                   ";
                                            cout << "| ";
                                            cout << tempPie;
                                            cout << "\n_______________________________________________________________________________________________________________________\n";
                                            cout << "\n\nΑν είσαι σίγουρος ότι θες να προσθέσεις το προϊόν με αυτά τα χαρακτηριστικα\n";
                                            cout << "πάτησε ENTER               0.Πίσω\n";
                                            cout << "            ";
                                            cin.get(beSure);
                                            if(cin.get() == '\n'){
                                                breakCount++;
                                                break;
                                            }
                                            else{
                                                breakCount--;
                                                break;
                                            }
                                            if(breakCount == 6) break;
										}
										if(breakCount == 6) break;
									}
									if(breakCount == 6) break;
							}
							if(breakCount == 6) break;
						}
						if(breakCount == 6) break;
					}
					if(breakCount == 6){
						martDeco.addItemMade(tempDi, tempCode, tempDes, tempWho, tempSale, tempPie);
						madeFileDi.open("MART_DECO_Di.txt");
						madeFileCode.open("MART_DECO_code.txt");
						madeFileDes.open("MART_DECO_description.txt");
						madeFilePr.open("MART_DECO_price_stock.txt");
						martDeco.madeDisplayFile(martDeco.madeRoot);
						madeFileDi.close();
						madeFileCode.close();
						madeFileDes.close();
						madeFilePr.close();
						break;
					}
					}
					system("cls");
					break;
				case 3:
				    system("cls");
				    cin.ignore(256, '\n');
				    while(true){
                         //CAUTION
                        cout << "****\n****Δώσε τον κωδικο προϊόντος LEXON για τροποποίηση:_                  0.Πίσω\n";
                        cout <<       "                                                    ";
                        getline(cin, pieCode, '\n');
                        if(pieCode == "0") break;
                        else{
                            found == false;
                            martDeco.findMadeCode(pieCode, martDeco.madeRoot);
                            while(!found){
                                cout << "\n****Ο κωδικός δεν βρέθηκε. Ξαναδοκιμάστε με καινούριο κωδικό:_                  0.Πίσω";
                                cout << "\n                                                             ";
                                getline(cin, pieCode, '\n');
                                martDeco.findMadeCode(pieCode, martDeco.madeRoot);
                                if(pieCode == "0") break;
                            }
                            if(found){
                                martDeco.madeDisplayOne(pieCode, martDeco.madeRoot);
                                cout << "****Δώστε το νέο απόθεμα του προϊόντος με αυτά τα στοιχεία_\n";
                                cout << "                                                          ";
                                cin >> newPie;
                                while(cin.fail()){
                                    cin.clear();
                                    cin.ignore();
                                    cout << "\n****Μη αποδεκτός αριθμός. Παρακαλώ ξαναδοκιμάστε: ";
                                    cin >> newPie;
                                }
                                martDeco.changeMadePiece(pieCode, martDeco.madeRoot, newPie);
                                madeFileDi.open("MART_DECO_Di.txt");
                                madeFileCode.open("MART_DECO_code.txt");
                                madeFileDes.open("MART_DECO_description.txt");
                                madeFilePr.open("MART_DECO_price_stock.txt");
                                martDeco.madeDisplayFile(martDeco.madeRoot);
                                madeFileDi.close();
                                madeFileCode.close();
                                madeFileDes.close();
                                madeFilePr.close();
                                cout << "\n_____________________________________________\n";
                                cout << "****Τα νέα χαρακτηριστικά του προϊόντος είναι";
                                martDeco.madeDisplayOne(pieCode, martDeco.madeRoot);
                                while(true){
                                    cout << "\n****Για επιστροφή στο μενού της LEXON";
                                    cout << "\n****Πάτησε ENTER";
                                    cin.get(beSure);
                                    if(cin.get() == '\n') break;
                                }
                            }
                        }
                        break;
				    }
				    system("cls");
					break;
				case 4:
				    system("cls");
				    if(martDeco.madeRoot == NULL){
						cout << "\n\n****ΔΕΝ ΥΠΑΡΧΟΥΝ ΠΡΟΪΟΝΤΑ";
						while(true){
							cout << "\n****Πάτησε ENTER";
							cin.get(next);
							if(cin.get() == '\n') break;
                        }
                        system("cls");
						break;
				    }
				    else{
				    cout << "\n****Αποθέματα LEXON που χρειάζονται ανανέωση\n";
				    martDeco.toRestoreDisplay(martDeco.madeRoot);
				    while(true){
                        cout << "\n****Πάτησε ENTER";
                        cin.get(next);
                        if(cin.get() == '\n') break;
                    }
                    system("cls");
                    break;
				    }
                case 5:
                    system("cls");
                    fromChoice = false;
                    while(1){
                    found = false;
                    cin.ignore(256, '\n');
                    cout << "\n****Δώσε κωδικό προϊόντος προς διαγραφή_\t0.Πίσω\n";
                    cout <<   "                                       ";
                    getline(cin, delCode, '\n');
                    if(delCode == "0") break;
                    martDeco.findMadeCode(delCode, martDeco.madeRoot);
                    while(!found){
                        cout << "\n****Ο κωδικός δεν βρέθηκε. Ξαναδοκιμάστε με καινούριο κωδικό:_                  0.Πίσω";
                        cout << "\n                                                             ";
                        getline(cin, delCode, '\n');
                        martDeco.findMadeCode(delCode, martDeco.madeRoot);
                        if(delCode == "0") break;
                    }
                    if(found){
                        cout << "\n****Αν είσαι σίγουρος ότι θες να διαγράψεις τον κωδικό " << delCode << " πληκτρολόγησε τη λέξη 'yes':___\t0.Πίσω";
                        cout << "\n                                                       ";
                        for(delLength = 0; delLength < delCode.size(); delLength++) cout << " ";
                        cout << "                             ";
                        cin >> yes;
                        if(yes != "yes") continue;
                        martDeco.madeDeleteNode(delCode);
                        madeFileDi.open("MART_DECO_Di.txt");
						madeFileCode.open("MART_DECO_code.txt");
						madeFileDes.open("MART_DECO_description.txt");
						madeFilePr.open("MART_DECO_price_stock.txt");
						martDeco.madeDisplayFile(martDeco.madeRoot);
						madeFileDi.close();
						madeFileCode.close();
						madeFileDes.close();
						madeFilePr.close();
                        cout << "\n****\n****Ο κωδικός " << delCode << " διαγράφηκε.";
                        cout <<       "\n--------------";
                        for(delLength = 0; delLength < delCode.size(); delLength++) cout << "-";
                        cout << "------------";
                        while(true){
                            cout << "\n****Πάτησε ENTER";
                            cin.get(delOk);
                            if(cin.get() == '\n') break;
                        }

                    }
                    break;
                    }
                    system("cls");
                    break;
				case 0:
					goBack = true;
					break;
                    }
                }
            break;

		case 8:
		    system("cls");
		    backFromWho = false;
			goBack = false;
			while(!goBack){
			cout << "\n*******************PARKER******PARKER******PARKER**********************\n";
			cout << "|                                                                     |\n";
    		cout << "|                                                                     |\n";
   	 		cout << "|        Διάλεξε Ενέργεια:                                            |\n";
   			cout << "|                                                                     |\n";
   			cout << "|        1.Δες όλα τα αποθέματα                                       |\n";
	   	 	cout << "|        2.Πρόσθεσε ένα κωδικό                                        |\n";
	    	cout << "|        3.Τροποποίησε ένα απόθεμα                                    |\n";
    		cout << "|        4.Δες τα αποθέματα που χρειάζονται ανανέωση                  |\n";
    		cout << "|        5.Διέγραψε έναν κωδικό                                       |\n";
    		cout << "|                                                                     |\n";
    		cout << "| Για επιστροφή στο Μενού πατήστε 0                                   |\n";
    		cout << "|                                                                     |\n";
    		cout << "*******************PARKER******PARKER******PARKER**********************\n";
    		cout << "****Δώσε τον αντίστοιχο αριθμό: ";
    		cin >> choicePar;
    		while(choicePar < 0 || choicePar > 5 || cin.fail()){
				cin.clear();
				cin.ignore();
				cout << "****Μη αποδεκτός αριθμός. Παρακαλώ ξαναδοκιμάστε: ";
				cin >> choicePar;
			}
			fromChoice = true;
			switch(choicePar){
				case 1:
				    system("cls");
					if(parker.parRoot == NULL){
						cout << "\n\n****ΔΕΝ ΥΠΑΡΧΟΥΝ ΠΡΟΪΟΝΤΑ";
						while(true){
							cout << "\n****Πάτησε ENTER";
							cin.get(next);
							if(cin.get() == '\n') break;
						}
						system("cls");
						break;
					}
					else{
                        cout << "\n-----------------------------------------------------------------------------------------------------------------------";
                        cout << "\n\t\t\t\t\t\t   ΑΠΟΘΕΜΑΤΑ PARKER";
                        cout << "\n-----------------------------------------------------------------------------------------------------------------------\n";
                        cout << "\nΚωδικός Design In | Κωδικός Προϊόντος | Περιγραφή Προϊόντος | Χονδρική Τιμή με Φ.Π.Α. | Λιανική Τιμή με Φ.Π.Α | Τεμάχια";
						cout << "\n_______________________________________________________________________________________________________________________\n\n";
						parker.parDisplay(parker.parRoot);
						while(true){
							cout << "\n****Πάτησε ENTER";
							cin.get(next);
							if(cin.get() == '\n') break;
						}
						system("cls");
						break;
					}
				case 2:
				    system("cls");
					breakCount = 0;
					while(true){
                        found = false;
						if(fromChoice) cin.ignore(256, '\n');
						fromChoice = false;
						cout << "\n****Δώσε κωδικό προϊόντος_\t\t0.Πίσω\n";
						cout <<   "                         ";
						getline(cin, tempCode, '\n');
						parker.findParCode(tempCode, parker.parRoot);
						if(tempCode == "0") break;
                        else if(found){
                            cout << "\n****Ο κωσικός που εισάγατε υπάρχει ήδη.\n";
                            cout << "Πάτησε ENTER";
                            cin.get(beSure);
                            if(cin.get() == '\n'){
                                break;
                            }
                        }
						else breakCount++;
						while(true){
							cout << "\n****Δώσε κωδικό Design In_\t\t0.Πίσω\n";
							cout <<   "                         ";
							getline(cin, tempDi, '\n');
							if(tempDi == "0"){
								breakCount--;
								break;
							}
							else breakCount++;
							while(true){
								cout << "\n****Δώσε περιγραφή προϊόντος_\t\t0.Πίσω\n";
								cout <<   "                            ";
								if(backFromWho) cin.ignore(256, '\n');
								getline(cin, tempDes, '\n');
								backFromWho = false;
								if(tempDes == "0"){
									breakCount--;
									break;
								}
								else breakCount++;
								while(true){
									cout << "\n****Δώσε χονδρική τιμή πώλησης_\t\t0.Πίσω\n";
									cout <<   "                              ";
									cin >> tempWho;
									while(cin.fail()){
											cin.clear();
											cin.ignore();
											cout << "****Μη αποδεκτός αριθμός. Παρακαλώ ξαναδοκιμάστε: ";
											cin >> tempWho;
									}
									if(tempWho == 0){
                                        backFromWho = true;
										breakCount--;
										break;
									}
									else{
										tempSale = 2.5 * tempWho;
										breakCount++;
									}
									while(true){
										cout << "\n****Δώσε αριθμό τεμαχίων_\t\t0.Πίσω\n";
										cout <<   "                        ";
										cin >> tempPie;
										while(cin.fail()){
											cin.clear();
											cin.ignore();
											cout << "****Μη αποδεκτός αριθμός. Παρακαλώ ξαναδοκιμάστε: ";
											cin >> tempPie;
										}
										if(tempPie == 0){
											breakCount--;
											break;
										}
                                        else breakCount++;
										while(true){
                                            cout << "\n_______________________________________________________________________________________________________________________\n\n";
                                            cout << tempDi;
                                            for(blanks = 0; blanks < 18 - tempDi.size(); blanks++) cout << " ";
                                            cout << "| ";
                                            cout << tempCode;
                                            for(blanks = 0; blanks < 18 - tempCode.size(); blanks++) cout << " ";
                                            cout << "| ";
                                            cout << tempDes;
                                            for(blanks = 0; blanks < 20 - tempDes.size(); blanks++) cout << " ";
                                            cout << "| ";
                                            cout << tempWho;
                                            cout << "                   ";
                                            cout << "| ";
                                            cout << tempSale;
                                            cout << "                   ";
                                            cout << "| ";
                                            cout << tempPie;
                                            cout << "\n_______________________________________________________________________________________________________________________\n";
                                            cout << "\n\nΑν είσαι σίγουρος ότι θες να προσθέσεις το προϊόν με αυτά τα χαρακτηριστικα\n";
                                            cout << "πάτησε ENTER               0.Πίσω\n";
                                            cout << "            ";
                                            cin.get(beSure);
                                            if(cin.get() == '\n'){
                                                breakCount++;
                                                break;
                                            }
                                            else{
                                                breakCount--;
                                                break;
                                            }
                                            if(breakCount == 6) break;
										}
										if(breakCount == 6) break;
									}
									if(breakCount == 6) break;
							}
							if(breakCount == 6) break;
						}
						if(breakCount == 6) break;
					}
					if(breakCount == 6){
						parker.addItemPar(tempDi, tempCode, tempDes, tempWho, tempSale, tempPie);
						parFileDi.open("PARKER_Di.txt");
						parFileCode.open("PARKER_code.txt");
						parFileDes.open("PARKER_description.txt");
						parFilePr.open("PARKER_price_stock.txt");
						parker.parDisplayFile(parker.parRoot);
						parFileDi.close();
						parFileCode.close();
						parFileDes.close();
						parFilePr.close();
						break;
					}
					}
					system("cls");
					break;
				case 3:
				    system("cls");
				    cin.ignore(256, '\n');
				    while(true){
                         //CAUTION
                        cout << "****\n****Δώσε τον κωδικο προϊόντος LEXON για τροποποίηση:_                  0.Πίσω\n";
                        cout <<       "                                                    ";
                        getline(cin, pieCode, '\n');
                        if(pieCode == "0") break;
                        else{
                            found == false;
                            parker.findParCode(pieCode, parker.parRoot);
                            while(!found){
                                cout << "\n****Ο κωδικός δεν βρέθηκε. Ξαναδοκιμάστε με καινούριο κωδικό:_                  0.Πίσω";
                                cout << "\n                                                             ";
                                getline(cin, pieCode, '\n');
                                parker.findParCode(pieCode, parker.parRoot);
                                if(pieCode == "0") break;
                            }
                            if(found){
                                parker.parDisplayOne(pieCode, parker.parRoot);
                                cout << "****Δώστε το νέο απόθεμα του προϊόντος με αυτά τα στοιχεία_\n";
                                cout << "                                                          ";
                                cin >> newPie;
                                while(cin.fail()){
                                    cin.clear();
                                    cin.ignore();
                                    cout << "\n****Μη αποδεκτός αριθμός. Παρακαλώ ξαναδοκιμάστε: ";
                                    cin >> newPie;
                                }
                                parker.changeParPiece(pieCode, parker.parRoot, newPie);
                                parFileDi.open("PARKER_Di.txt");
                                parFileCode.open("PARKER_code.txt");
                                parFileDes.open("PARKER_description.txt");
                                parFilePr.open("PARKER_price_stock.txt");
                                parker.parDisplayFile(parker.parRoot);
                                parFileDi.close();
                                parFileCode.close();
                                parFileDes.close();
                                parFilePr.close();
                                cout << "\n_____________________________________________\n";
                                cout << "****Τα νέα χαρακτηριστικά του προϊόντος είναι";
                                parker.parDisplayOne(pieCode, parker.parRoot);
                                while(true){
                                    cout << "\n****Για επιστροφή στο μενού της LEXON";
                                    cout << "\n****Πάτησε ENTER";
                                    cin.get(beSure);
                                    if(cin.get() == '\n') break;
                                }
                            }
                        }
                        break;
				    }
				    system("cls");
					break;
				case 4:
				    system("cls");
				    if(parker.parRoot == NULL){
						cout << "\n\n****ΔΕΝ ΥΠΑΡΧΟΥΝ ΠΡΟΪΟΝΤΑ";
						while(true){
							cout << "\n****Πάτησε ENTER";
							cin.get(next);
							if(cin.get() == '\n') break;
                        }
                        system("cls");
						break;
				    }
				    else{
				    cout << "\n****Αποθέματα PARKER που χρειάζονται ανανέωση\n";
				    parker.toRestoreDisplay(parker.parRoot);
				    while(true){
                        cout << "\n****Πάτησε ENTER";
                        cin.get(next);
                        if(cin.get() == '\n') break;
                    }
                    system("cls");
                    break;
				    }
                case 5:
                    system("cls");
                    fromChoice = false;
                    while(1){
                    found = false;
                    cin.ignore(256, '\n');
                    cout << "\n****Δώσε κωδικό προϊόντος προς διαγραφή_\t0.Πίσω\n";
                    cout <<   "                                       ";
                    getline(cin, delCode, '\n');
                    if(delCode == "0") break;
                    parker.findParCode(delCode, parker.parRoot);
                    while(!found){
                        cout << "\n****Ο κωδικός δεν βρέθηκε. Ξαναδοκιμάστε με καινούριο κωδικό:_                  0.Πίσω";
                        cout << "\n                                                             ";
                        getline(cin, delCode, '\n');
                        parker.findParCode(delCode, parker.parRoot);
                        if(delCode == "0") break;
                    }
                    if(found){
                        cout << "\n****Αν είσαι σίγουρος ότι θες να διαγράψεις τον κωδικό " << delCode << " πληκτρολόγησε τη λέξη 'yes':___\t0.Πίσω";
                        cout << "\n                                                       ";
                        for(delLength = 0; delLength < delCode.size(); delLength++) cout << " ";
                        cout << "                             ";
                        cin >> yes;
                        if(yes != "yes") continue;
                        parker.parDeleteNode(delCode);
                        parFileDi.open("PARKER_Di.txt");
						parFileCode.open("PARKER_code.txt");
						parFileDes.open("PARKER_description.txt");
						parFilePr.open("PARKER_price_stock.txt");
						parker.parDisplayFile(parker.parRoot);
						parFileDi.close();
						parFileCode.close();
						parFileDes.close();
						parFilePr.close();
                        cout << "\n****\n****Ο κωδικός " << delCode << " διαγράφηκε.";
                        cout <<       "\n--------------";
                        for(delLength = 0; delLength < delCode.size(); delLength++) cout << "-";
                        cout << "------------";
                        while(true){
                            cout << "\n****Πάτησε ENTER";
                            cin.get(delOk);
                            if(cin.get() == '\n') break;
                        }

                    }
                    break;
                    }
                    system("cls");

                    break;

				case 0:
					goBack = true;
					break;
                    }
                }
        break;

		case 0:
			return 0;
			break;
		}

	}



}



