typedef struct _TableSection {
    const char** cells;        // celulas da tabela
    char* align;               // alinhamento de cada celula 'l'/'r'/'c' para esquerda/direita/centro
    unsigned* width;           // largura de cada célula
    unsigned len;              // quantidade de celulas
}TableSectionInfo;

typedef struct _Table {
    const char borders[2];     // <0 vertical> <1 horizontal> <2 vértice>
    const char separator;      // separador interno
    TableSectionInfo header;   // celulas de cabeçalho, len representa o numero de colunas
    TableSectionInfo body;     // celulas do corpo, len representa o numero de linhas,  [len][header.len]
    TableSectionInfo footer;   // celulas do rodape, len representa o numero de colunas
}TableInfo;

void makeTable(){

    printf("    #-----------------------------------------------------#\n");
	printf("    |        nome       |  maximo  |  minimo  |   media   |\n");
	printf("    |-----------------------------------------------------|\n");
	for (unsigned int i = 0; i < BenchTable.buffered; i++) {
		function = BenchTable.function[i];
		average = 0;
		minimum = LONG_MAX;
		maximum = 0;
		for (int e = 0; e < BenchTable.average[i]; e++) {
			printf("\r    [%i/%i] [%s... [%i/%i]]",  i + 1,  BenchTable.buffered, BenchTable.name[i], e+1, BenchTable.average[i]);
			
			counter = clock();
			PyObject_CallObject(function, NULL);
			counter = clock() - counter;

			average += counter;
			minimum = min(minimum, counter);
			maximum = max(maximum, counter);
		}

		average /= BenchTable.average[i];
		total += average;

		printf("\r    |%-19s|%10li|%10li|%11li|   \n", BenchTable.name[i], average, minimum, maximum);
	}
	printf("    |-----------------------------------------------------|\n");
	printf("    | total | %-44li|\n", total);
	printf("    #-----------------------------------------------------#\n");
}