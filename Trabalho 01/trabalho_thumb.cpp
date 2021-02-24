#include <bits/stdc++.h>

using namespace std;

/*
	Entrada: A entrada será uma string de 4 caracteres que representa um número em hexadecimal
	Saída: A saída será uma string com 16 caracteres que tem a representação em binário do número em hexadecimal
*/
string hexa_para_binario(string s) {
	string out;
	for (char &c : s) {
		uint16_t n;
		c = tolower(c);
		if ('0' <= c and c <= '9') {
			n = (c-'0');
		} else {
			n = (c-'a') + 10;
		}
		for (int i = 3; i >= 0; --i) {
			if (n & (1 << i)) {
				out += "1";
			} else {
				out += "0";
			}
		}
	}
	return out;
}

/*
	Entrada: String binária com 16 caracteres
	Saída: uint16_teiro contendo o valor na base 10
*/
uint16_t string_binaria_para_uint16_teiro(string s) {
	reverse(s.begin(), s.end());
	uint16_t val = 0;
	uint16_t pot = 1;
	for (char c : s) {
		val = val + (c-'0') * pot;
		pot *= 2;
	}
	return val;
}

/*
	Entrada: uma string e um l e r que representa o valor que quero transformar em uint16_teiro
	Saída: o uint16_teiro convertido da base 2 para a base 10 que estava entre as posições l e r da string de entrada
*/
uint16_t pegar_valor(string linha, uint16_t l, uint16_t r) {
	uint16_t qtd = r-l+1;
	string aux = linha.substr(l, qtd);
	uint16_t val = string_binaria_para_uint16_teiro(aux);
	return val;
}

int main() {
	/*
		Variáveis auxiliares para uso das instruções
		BLX ((instruction+4+(poff<<12)+offset*4) &~ 3)
		e
		BL instruction+4+(poff<<12)+offset*2
	*/
	int16_t poff = -1;
	uint16_t timer = 0;
	uint16_t timer_poff = 0;

	string linha, resposta;
	while (getline(cin, linha)) {
		++timer;
		if (poff != -1 and timer_poff+1 < timer) {
			cout << "Instrução inválida\n";
			exit(0);
		}

		resposta += linha + ":  ";

		linha = hexa_para_binario(linha);

		string ins = linha.substr(0, 4);

		if (ins == "0000") {
			//LSL | LSR
			if (linha[4] == '0') {
				resposta += "LSL ";
			} else {
				resposta += "LSR ";
			}
			uint16_t immed5 = pegar_valor(linha, 5, 9);
			uint16_t lm = pegar_valor(linha, 10, 12);
			uint16_t ld = pegar_valor(linha, 13, 15);
			resposta += "r" + to_string(ld) + ", " + "r" + to_string(lm) + ", #" + to_string(immed5) + "\n";
		} else if (ins == "0001") {
			if (linha[4] == '0') {
				//ASR
				resposta += "ASR ";
				uint16_t immed5 = pegar_valor(linha, 5, 9);
				uint16_t ln = pegar_valor(linha, 10, 12);
				uint16_t ld = pegar_valor(linha, 13, 15);
				resposta += "r" + to_string(ld) + ", " + "r" + to_string(ln) + ", #" + to_string(immed5) + "\n";
			} else {
				if (linha[5] == '0') {
					//ADD | SUB
					if (linha[6] == '0') {
						resposta += "ADD ";
					} else {
						resposta += "SUB ";
					}
					uint16_t lm = pegar_valor(linha, 7, 9);
					uint16_t ln = pegar_valor(linha, 10, 12);
					uint16_t ld = pegar_valor(linha, 13, 15);
					resposta += "r" + to_string(ld) + ", r" + to_string(ln) + ", r" + to_string(lm) + "\n";
				} else {
					//ADD | SUB
					if (linha[6] == '0') {
						resposta += "ADD ";
					} else {
						resposta += "SUB ";
					}
					uint16_t immed3 = pegar_valor(linha, 7, 9);
					uint16_t ln = pegar_valor(linha, 10, 12);
					uint16_t ld = pegar_valor(linha, 13, 15);
					resposta += "r" + to_string(ld) + ", " + to_string(ln) + ", #" + to_string(immed3) + "\n";
				}
			}
		} else if (ins == "0010") {
			//MOV | CMP
			if (linha[4] == '0') {
				resposta += "MOV ";
			} else {
				resposta += "CMP ";
			}
			uint16_t ln = pegar_valor(linha, 5, 7);
			uint16_t immed8 = pegar_valor(linha, 8, 15);
			resposta += "r" + to_string(ln) + ", #" + to_string(immed8) + "\n";
		} else if (ins == "0011") {
			//ADD | SUB
			if (linha[4] == '0') {
				resposta += "ADD ";
			} else {
				resposta += "SUB ";
			}
			uint16_t ld = pegar_valor(linha, 5, 7);
			uint16_t immed8 = pegar_valor(linha, 8, 15);
			resposta += "r" + to_string(ld) + ", #" + to_string(immed8) + "\n";
		} else if (ins == "0100") {
			if (linha[4] == '0') {
				if (linha[5] == '0') {
					if (linha[6] == '0') {
						if (linha[7] == '0') {
							//AND | EOR | LSL | LSR
							string op = linha.substr(8, 2);
							if (op == "00") {
								resposta += "AND ";
							} else if (op == "01") {
								resposta += "EOR ";
							} else if (op == "10") {
								resposta += "LSL ";
							} else {
								resposta += "LSR ";
							}
							uint16_t ls = pegar_valor(linha, 10, 12);
							uint16_t ld = pegar_valor(linha, 13, 15);
							resposta += "r" + to_string(ld) + ", r" + to_string(ls) + "\n";
						} else {
							//ASR | ADC | SBC | ROR
							string op = linha.substr(8, 2);
							if (op == "00") {
								resposta += "ASR ";
							} else if (op == "01") {
								resposta += "ADC ";
							} else if (op == "10") {
								resposta += "SBC ";
							} else {
								resposta += "ROR ";
							}
							uint16_t lm = pegar_valor(linha, 10, 12);
							uint16_t ld = pegar_valor(linha, 13, 15);
							resposta += "r" + to_string(ld) + ", r" + to_string(lm) + "\n";
						}
					} else {
						if (linha[7] == '0') {
							//TST | NEG | CMP | CMN
							string op = linha.substr(8, 2);
							if (op == "00") {
								resposta += "TST ";
							} else if (op == "01") {
								resposta += "NEG ";
							} else if (op == "10") {
								resposta += "CMP ";
							} else {
								resposta += "CMN ";
							}
							uint16_t lm = pegar_valor(linha, 10, 12);
							uint16_t ld = pegar_valor(linha, 13, 15);
							resposta += "r" + to_string(ld) + ", r" + to_string(lm) + "\n";
						} else {
							//ORR | MUL | BIC | MVN
							string op = linha.substr(8, 2);
							if (op == "00") {
								resposta += "ORR ";
							} else if (op == "01") {
								resposta += "MUL ";
							} else if (op == "10") {
								resposta += "BIC ";
							} else {
								resposta += "MVN ";
							}
							uint16_t lm = pegar_valor(linha, 10, 12);
							uint16_t ld = pegar_valor(linha, 13, 15);
							resposta += "r" + to_string(ld) + ", r" + to_string(lm) + "\n";
						}
					}
				} else {
					if (linha[7] == '0') {
						if (linha[8] == '0') {
							if (linha[9] == '0') {
								//CPY Ld, Lm
								resposta += "CPY ";
								uint16_t lm = pegar_valor(linha, 10, 12);
								uint16_t ld = pegar_valor(linha, 13, 15);
								resposta += "r" + to_string(ld) + ", r" + to_string(lm) + "\n";
							} else {
								//ADD | MOV Ld, Hm
								if (linha[6] == '0') {
									resposta += "ADD ";
								} else {
									resposta += "MOV ";
								}
								uint16_t lm = pegar_valor(linha, 10, 12);
								uint16_t ld = pegar_valor(linha, 13, 15);
								resposta += "r" + to_string(ld) + ", r" + to_string(lm) + "\n";
							}
						} else {
							if (linha[9] == '0') {
								//ADD | MOV Hd, Lm
								if (linha[6] == '0') {
									resposta += "ADD ";
								} else {
									resposta += "MOV ";
								}
								uint16_t lm = pegar_valor(linha, 10, 12);
								uint16_t ld = pegar_valor(linha, 13, 15);
								resposta += "r" + to_string(ld) + ", r" + to_string(lm) + "\n";
							} else {
								//ADD | MOV Hd, Hm
								if (linha[6] == '0') {
									resposta += "ADD ";
								} else {
									resposta += "MOV ";
								}
								uint16_t lm = pegar_valor(linha, 10, 12);
								uint16_t ld = pegar_valor(linha, 13, 15);
								resposta += "r" + to_string(ld) + ", r" + to_string(lm) + "\n";
							}
						}
					} else {
						if (linha[6] == '0') {
							if (linha[8] == '0') {
								if (linha[9] == '1') {
									//CMP
									resposta += "CMP ";
									uint16_t lm = pegar_valor(linha, 10, 12);
									uint16_t ln = pegar_valor(linha, 13, 15);
									resposta += "r" + to_string(ln) + ", r" + to_string(lm) + "\n";
								}
							} else {
								if (linha[9] == '0') {
									//CMP
									resposta += "CMP ";
									uint16_t lm = pegar_valor(linha, 10, 12);
									uint16_t ln = pegar_valor(linha, 13, 15);
									resposta += "r" + to_string(ln) + ", r" + to_string(lm) + "\n";
								} else {
									//CMP
									resposta += "CMP ";
									uint16_t lm = pegar_valor(linha, 10, 12);
									uint16_t ln = pegar_valor(linha, 13, 15);
									resposta += "r" + to_string(ln) + ", r" + to_string(lm) + "\n";
								}	
							}
						} else {
							//BX | BLX
							if (linha[8] == '0') {
								resposta += "BX ";
							} else {
								resposta += "BLX ";
							}
							uint16_t rm = pegar_valor(linha, 9, 12);
							resposta += "r" + to_string(rm) + "\n";
						}
					}
				}
			} else {
				//LDR Ld, [pc, #immed*4]
				resposta += "LDR ";
				uint16_t ld = pegar_valor(linha, 5, 7);
				uint16_t immed8 = pegar_valor(linha, 8, 15);
				resposta += "r" + to_string(ld) + ", [pc, #" + to_string(immed8*4) + "]\n";
			}
		} else if (ins == "0101") {
			if (linha[4] == '0') {
				//STR | STRH | STRB | LDRSB pre
				string op = linha.substr(5, 2);
				if (op == "00") {
 					resposta += "STR ";
				} else if (op == "01") {
 					resposta += "STRH ";
				} else if (op == "10") {
 					resposta += "STRB ";
				} else {
 					resposta += "LDRSB ";
				}
				uint16_t lm = pegar_valor(linha, 7, 9);
				uint16_t ln = pegar_valor(linha, 10, 12);
				uint16_t ld = pegar_valor(linha, 13, 15);
				resposta += "r" + to_string(ld) + ", [r" + to_string(ln) + ", r" + to_string(lm) + "]\n";
			} else {
				//LDR | LDRH | LDRB | LDRSH pre
				string op = linha.substr(5, 2);
				if (op == "00") {
 					resposta += "LDR ";
				} else if (op == "01") {
 					resposta += "LDRH ";
				} else if (op == "10") {
 					resposta += "LDRB ";
				} else {
 					resposta += "LDRSH ";
				}
				uint16_t lm = pegar_valor(linha, 7, 9);
				uint16_t ln = pegar_valor(linha, 10, 12);
				uint16_t ld = pegar_valor(linha, 13, 15);
				resposta += "r" + to_string(ld) + ", [r" + to_string(ln) + ", r" + to_string(lm) + "]\n";
			}
		} else if (ins == "0110") {
			//STR | LDR Ld, [Ln, #immed*4]
				if (linha[4] == '0') {
 					resposta += "STR ";
				} else {
 					resposta += "LDR ";
				}
				uint16_t immed5 = pegar_valor(linha, 5, 9);
				uint16_t ln = pegar_valor(linha, 10, 12);
				uint16_t ld = pegar_valor(linha, 13, 15);
				resposta += "r" + to_string(ld) + ", [r" + to_string(ln) + ", #" + to_string(immed5*4) + "]\n";
		} else if (ins == "0111") {
			//STRB | LDRB Ld, [Ln, #immed]
				if (linha[4] == '0') {
 					resposta += "STRB ";
				} else {
 					resposta += "LDRB ";
				}
				uint16_t immed5 = pegar_valor(linha, 5, 9);
				uint16_t ln = pegar_valor(linha, 10, 12);
				uint16_t ld = pegar_valor(linha, 13, 15);
				resposta += "r" + to_string(ld) + ", [r" + to_string(ln) + ", #" + to_string(immed5) + "]\n";
		} else if (ins == "1000") {
			//STRH | LDRH Ld, [Ln, #immed*2]
				if (linha[4] == '0') {
 					resposta += "STRH ";
				} else {
 					resposta += "LDRH ";
				}
				uint16_t immed5 = pegar_valor(linha, 5, 9);
				uint16_t ln = pegar_valor(linha, 10, 12);
				uint16_t ld = pegar_valor(linha, 13, 15);
				resposta += "r" + to_string(ld) + ", [r" + to_string(ln) + ", #" + to_string(immed5*2) + "]\n";
		} else if (ins == "1001") {
			//STR | LDR Ld, [sp, #immed*4]
				if (linha[4] == '0') {
 					resposta += "STR ";
				} else {
 					resposta += "LDR ";
				}
				uint16_t ld = pegar_valor(linha, 5, 7);
				uint16_t immed8 = pegar_valor(linha, 5, 15);
				resposta += "r" + to_string(ld) + ", [sp, #" + to_string(immed8*4) + "]\n";
		} else if (ins == "1010") {
			//ADD Ld, pc, #immed*4 | ADD Ld, sp, #immed*4
			resposta += "ADD ";
			uint16_t ld = pegar_valor(linha, 5, 7);
			uint16_t immed8 = pegar_valor(linha, 8, 15);
			resposta += "r" + to_string(ld) + ", " + (linha[4] == '0' ? "pc" : "sp") + ", #" + to_string(immed8*4) + "\n";
		} else if (ins == "1011") {
			if (linha[5] == '0') {
				if (linha[4] == '0') {
					if (linha[6] == '0') {
						//ADD sp, #immed*4 | SUB sp,#immed*4
						if (linha[8] == '0') {
							resposta += "ADD ";
						} else {
							resposta += "SUB ";
						}
						uint16_t immed7 = pegar_valor(linha, 9, 15);
						resposta += "sp, #" + to_string(immed7*4) + "\n";
					} else {
						//SXTH | SXTB | UXTH | UXTB
						string op = linha.substr(8, 2);
						if (op == "00") {
							resposta += "SXTH ";
						} else if (op == "01") {
							resposta += "SXTB ";
						} else if (op == "10") {
							resposta += "UXTH ";
						} else {
							resposta += "UXTB ";
						}
						uint16_t lm = pegar_valor(linha, 10, 12);
						uint16_t ld = pegar_valor(linha, 13, 15);
						resposta += "r" + to_string(ld) + ", r" + to_string(lm) + "\n";
					}
				} else {
					//REV | REV16 | | REVSH
					string op = linha.substr(8, 2);
					if (op == "00") {
						resposta += "REV ";
					} else if (op == "01") {
						resposta += "REV16 ";
					} else if (op == "10") {
						cout << "Instrução Inválida\n";
						exit(0);
					} else if (op == "11") {
						resposta += "REVSH ";
					}
					uint16_t lm = pegar_valor(linha, 10, 12);
					uint16_t ld = pegar_valor(linha, 13, 15);
					resposta += "r" + to_string(ld) + ", r" + to_string(lm) + "\n";
				}
			} else {
				if (linha[6] == '0') {
					//PUSH | POP
					if (linha[4] == '0') {
						resposta += "PUSH ";
					} else {
						resposta += "POP ";
					}
					resposta += "{";
					bool eh_primeiro_elemento = true;
					for (int i = 15; i >= 8; --i) {
						uint16_t bit = 15-i;
						if (linha[i] == '1') {
							if (eh_primeiro_elemento) {
								resposta += "r" + to_string(bit);
							} else {
								resposta += ", r" + to_string(bit);
							}
							eh_primeiro_elemento = false;
						}
					}
					uint16_t R = linha[7]-'0';
					if (R) {
						if (eh_primeiro_elemento) {
							if (linha[4] == '0') {
								resposta += "lr";
							} else {
								resposta += "pc";
							}
						} else {
							resposta += ", ";
							if (linha[4] == '0') {
								resposta += "lr";
							} else {
								resposta += "pc";
							}
						}
					}
					resposta += "}\n";
				} else {
					if (linha[4] == '0') {
						if (linha[10] == '0') {
							//SETEND LE | SETEND BE
							if (linha[12] == '0') {
								resposta += "SETEND LE\n";
							} else {
								resposta += "SETEND BE\n";
							}
						} else {
							//CPSIE | CPSID
							if (linha[11] == '0') {
								resposta += "CPSIE ";
							} else {
								resposta += "CPSID ";
							}
							if (linha[13] == '1') {
								resposta += "a";
							}
							if (linha[14] == '1') {
								resposta += "i";
							}
							if (linha[15] == '1') {
								resposta += "f";
							}
							resposta += "\n";
						}
					} else {
						//BKPT immed8
						uint16_t immed8 = pegar_valor(linha, 8, 15);
						resposta += "BKPT #" + to_string(immed8) + "\n";
					}
				}
			}
		} else if (ins == "1100") {
			//STMIA | LDMIA Ln!, {register-list}
			if (linha[4] == '0') {
				resposta += "STMIA ";
			} else {
				resposta += "LDMIA ";
			}
			uint16_t ln = pegar_valor(linha, 5, 7);
			resposta += "r" + to_string(ln) + "!, ";
			resposta += "{";
			bool first = true;
			for (int i = 15; i >= 8; --i) {
				uint16_t bit = 16-i-1;
				if (linha[i] == '1') {
					if (first) {
						resposta += "r" + to_string(bit);
					} else {
						resposta += ", r" + to_string(bit);
					}
					first = false;
				}
			}
			resposta += "}\n";
		} else if (ins == "1101") {
			string aux = linha.substr(4, 4);
			if (aux == "1110") {
				//Undefined and expected to remain so
			} else if (aux == "1111") {
				//SWI immed8
				uint16_t immed8 = pegar_valor(linha, 8, 15);
				resposta += "SWI #" + to_string(immed8) + "\n";
			} else {
				//B<cond> instruction_address+4+offset*2
				resposta += "B";
				string cond = linha.substr(4, 4);
				if (cond == "0000") {
					resposta += "EQ ";
				} else if (cond == "0001") {
					resposta += "NE ";
				} else if (cond == "0010") {
					resposta += "CS ";
				} else if (cond == "0011") {
					resposta += "CC ";
				} else if (cond == "0100") {
					resposta += "MI ";
				} else if (cond == "0101") {
					resposta += "PL ";
				} else if (cond == "0110") {
					resposta += "VS ";
				} else if (cond == "0111") {
					resposta += "VC ";
				} else if (cond == "1000") {
					resposta += "HI ";
				} else if (cond == "1001") {
					resposta += "LS ";
				} else if (cond == "1010") {
					resposta += "GE ";
				} else if (cond == "1011") {
					resposta += "LT ";
				} else if (cond == "1100") {
					resposta += "GT ";
				} else if (cond == "1101") {
					resposta += "LE ";
				} else {
					cout << "Instrução Inválida\n";
					exit(0);
				}
				uint16_t offset = pegar_valor(linha, 8, 15);
				resposta += "#" + to_string(4+offset*2) + "\n";
			}
		} else if (ins == "1110") {
			if (linha[4] == '0') {
				//B instruction_address+4+offset*2
				uint16_t offset = pegar_valor(linha, 5, 15);
				resposta += "B #" + to_string(4+2*offset) + "\n";
			} else {
				//BLX ((instruction+4+(poff<<12)+offset*4) &~ 3)
				//This must be preceded by a branch prefix instruction.
				resposta += "BLX ";
				uint16_t offset = pegar_valor(linha, 5, 14);
				if (poff != -1 and timer_poff+1 == timer) {
					int16_t aux_poff = poff;
					uint16_t print = ((4+(aux_poff<<12)+offset*4) & ~3);
					resposta += to_string(print) + "\n";
				} else {
					cout << "Instrução Inválida\n";
					exit(0);
				}
				poff = -1;
				timer_poff = 0;
			}
		} else if (ins == "1111") {
			if (linha[4] == '0') {
				//This is the branch prefix instruction. It must be
				//followed by a relative BL or BLX instruction.
				poff = pegar_valor(linha, 5, 15);
				timer_poff = timer;
				resposta += to_string(poff) + "\n";
			} else {
				//BL instruction+4+(poff<<12)+offset*2
				//This must be preceded by a branch prefix instruction
				resposta += "BL ";
				uint16_t offset = pegar_valor(linha, 5, 14);
				if (poff != -1 and timer_poff+1 == timer) {
					uint16_t aux_poff = poff;
					uint16_t print = (4+(aux_poff<<12)+offset*2);
					resposta += to_string(print) + "\n";
				} else {
					cout << "Instrução Inválida\n";
					exit(0);
				}
				poff = -1;
				timer_poff = 0;
			}
		} else {
			cout << "Instrução Inválida\n";
			exit(0);
		}
	}

	cout << resposta;

}
