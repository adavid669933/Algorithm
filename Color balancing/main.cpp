
#include "main.h"
using namespace std;
/********************** Main Function ***********************/
int main() {

	// part 1
	{
		/********************* File Input ***********************/
		fstream infile("iccad2015_input.case5");

		string line;

		getline(infile, line, '=');
		getline(infile, line, '\n');
		ALPHA = stoi(line);

		getline(infile, line, '=');
		getline(infile, line, '\n');
		BETA = stoi(line);

		getline(infile, line, '=');
		getline(infile, line, '\n');
		OMEGA = stoi(line);

		// cout << ALPHA << endl << BETA << endl << OMEGA << endl;


		/********************* a.將array裡的值assign到struct vertex裡,以及設定vertex編號 *****************/
		int x1, y1, x2, y2;

		vertice_ptr = &vertice;
		int i = 0;
		while (!infile.eof()) {

			getline(infile, line, ',');
			if (line.length() != 0) {
				x1 = stoi(line);

				getline(infile, line, ',');
				y1 = stoi(line);

				getline(infile, line, ',');
				x2 = stoi(line);

				getline(infile, line, '\n');
				y2 = stoi(line);

				vertex temp;
				temp = AssignVertex(i, x1, y1, x2, y2);
				vertice.push_back(temp);
				i++;
				cout << x1 << "," << y1 << "," << x2 << "," << y2 << "," << i << endl;
			}
		}
		const int array_size = vertice.size();
		// cout << vertice.size() << endl;

		/************************************** b.Construct Link List ************************************/
		for (int i = 0; i < array_size; i++) {

			adjacent_vertex* adj_ptr_i = NULL;
			adjacent_vertex* adj_ptr_f = NULL;

			for (int j = 0; j <array_size; j++) {

				int number = ConstructLinkList(vertice, vertice.at(i), i, j, ALPHA, BETA);
				if (number != -1) {
					if (adj_ptr_i == NULL) {
						adj_ptr_i = new adjacent_vertex;
						adj_ptr_f = adj_ptr_i;
						adj_ptr_i->vertex_number = number;
					}
					else {
						adj_ptr_f->adjacent = new adjacent_vertex;
						adj_ptr_f->adjacent->vertex_number = number;
						adj_ptr_f = adj_ptr_f->adjacent;
					}
				}
			}
			vertice.at(i).adjacent = adj_ptr_i;
		}
		/*Test b.*/
		for (int i = 0; i < array_size; i++) {
			//cout << vertice.at(i).vertex_number << " ";
			if (vertice.at(i).adjacent != NULL) {

				adjacent_vertex* adj_ = vertice.at(i).adjacent;

				while (adj_ != NULL) {
					//cout << adj_->vertex_number << " ";
					adj_ = adj_->adjacent;
				}
			}
			//cout << endl;
		}
		/******************************************* c.Assign Color **************************************/
		for (int i = 0; i < array_size; i++) {
			if (vertice.at(i).shape_color == initial) {
				vertex* ptr = &vertice.at(i);
				SetColor(vertice_ptr, ptr, initial);
			}
		}
		/*Test c.*/
		for (int i = 0; i < array_size; i++) {
			//cout << vertice.at(i).vertex_number << " " << vertice.at(i).shape_color << " ";
			//cout << endl;
		}
		/*************************************** d. Assign Graph Number **********************************/
		for (int i = 0; i<array_size; i++) {
			if (vertice.at(i).graph == -1) {
				vertex* ptr = &vertice.at(i);
				SetGraph(vertice_ptr, ptr, graph);
				graph++;
			}
		}
		/* Test d.*/
		for (int i = 0; i < array_size; i++) {
			//cout << vertice.at(i).vertex_number << " " << vertice.at(i).graph << " ";
			//cout << endl;
		}
		/************************************* e. Find Color Bounding Box ********************************/

		int initial = 0;
		while (vertice.at(initial).shape_color != banned) {
			x1 = vertice.at(initial).position.x1;
			y1 = vertice.at(initial).position.y1;
			x2 = vertice.at(initial).position.x2;
			y2 = vertice.at(initial).position.y2;
			initial++;
			break;
		}
		for (int i = 0; i < array_size; i++) {
			if (vertice.at(i).position.x1 < x1&&vertice.at(i).shape_color != banned) {
				x1 = vertice.at(i).position.x1;
			}
			if (vertice.at(i).position.y1 < y1&&vertice.at(i).shape_color != banned) {
				y1 = vertice.at(i).position.y1;
			}
			if (vertice.at(i).position.x2 > x2&&vertice.at(i).shape_color != banned) {
				x2 = vertice.at(i).position.x2;
			}
			if (vertice.at(i).position.y2 > y2&&vertice.at(i).shape_color != banned) {
				y2 = vertice.at(i).position.y2;
			}
		}
		BoundingBox.x1 = x1;
		BoundingBox.y1 = y1;
		BoundingBox.x2 = x2;
		BoundingBox.y2 = y2;

		/* Test e.*/ //cout << BoundingBox.x1 << " " << BoundingBox.y1 << " " << BoundingBox.x2 << " " << BoundingBox.y2;

					 /*************************************************************************************************/
		infile.close();
		/************************************* prepare for part 2 ********************************/
		vertex_quantity = array_size;
	}

	// part 2
	draw_color(OMEGA, BoundingBox, graph, vertice_ptr, vertex_quantity, &window_quantity, windows);

	// test_part2
	{
		file.open("test_part2/part2.txt");
		file << vertex_quantity << " " << graph << " " << OMEGA << endl;
		file << BoundingBox.x1 << " " << BoundingBox.y1 << " " << BoundingBox.x2 << " " << BoundingBox.y2 << endl;
		for (int i = 0; i < vertex_quantity; i++)
			file << vertice[i].position.x1 << " " << vertice[i].position.y1 << " " << vertice[i].position.x2 << " " << vertice[i].position.y2 << " " << vertice[i].shape_color << " " << vertice[i].graph << endl;
		file.close();
	}

	cout << (double)clock() / CLOCKS_PER_SEC << " S";
	system("pause");
	return 0;
}

/******************************************** Main Function ******************************************/
vertex AssignVertex(int i, int x1, int y1, int x2, int y2) {

	vertex temp;
	temp.vertex_number = i;
	temp.position.x1 = x1;
	temp.position.y1 = y1;
	temp.position.x2 = x2;
	temp.position.y2 = y2;
	return temp;
	/*/ Test a.*/ //cout << temp.position.x1 << " " << temp.position.y1 << " " << temp.position.x2 << " " << temp.position.y2 << endl;
}
int ConstructLinkList(vector<vertex> vertice, vertex vertice_local, int i, int j, int ALPHA, int BETA) {

	if (i == j) {
		return -1;
	}
	int x1 = vertice_local.position.x1;
	int y1 = vertice_local.position.y1;
	int x2 = vertice_local.position.x2;
	int y2 = vertice_local.position.y2;

	int x1_ = vertice.at(j).position.x1;
	int y1_ = vertice.at(j).position.y1;
	int x2_ = vertice.at(j).position.x2;
	int y2_ = vertice.at(j).position.y2;

	if ((y1 <= y1_&& y1_ < y2) || (y1 < y2_&&y2_ <= y2) || (y1 > y1_&&y2 < y2_)) {

		int distance_1 = abs(x2 - x1_);
		int distance_2 = abs(x1 - x2_);

		if (distance_1 <= ALPHA || distance_2 <= ALPHA) {
			return j;
		}
		else {
			return -1;
		}
	}
	else if ((x1 <= x1_&&x1_ < x2) || (x1 < x2_&&x2_ <= x2) || (x1 > x1_&&x2 < x2_)) {

		int distance_1 = abs(y2 - y1_);
		int distance_2 = abs(y1 - y2_);

		if (distance_1 <= BETA || distance_2 <= BETA) {
			return j;
		}
		else {
			return -1;
		}
	}
	else {
		return -1;
	}
}
void SetColor(vector<vertex>* vertice_ptr, struct vertex* ptr, color color_) {

	if (ptr->shape_color == initial&&color_ == initial) {      // 情況一. 整條LinkList都還沒SetColor的時候
		ptr->shape_color = red;
		if (ptr->adjacent != NULL) {

			adjacent_vertex* adj_ = ptr->adjacent;

			while (adj_ != NULL) {
				adj_->shape_color = green;
				ptr = &(*vertice_ptr).at(adj_->vertex_number);
				SetColor(vertice_ptr, ptr, green);
				adj_ = adj_->adjacent;
			}
		}
	}
	else if (ptr->shape_color == initial&&color_ == red) {    // 情況二. 從LinkList的adjacent傳下來的顏色==red 
		ptr->shape_color = red;
		if (ptr->adjacent != NULL) {

			adjacent_vertex* adj_ = ptr->adjacent;

			while (adj_ != NULL) {
				adj_->shape_color = green;
				ptr = &(*vertice_ptr).at(adj_->vertex_number);
				SetColor(vertice_ptr, ptr, green);
				adj_ = adj_->adjacent;
			}
		}
	}
	else if (ptr->shape_color == initial&&color_ == green) {  // 情況三. 從LinkList的adjacent傳下來的顏色==green
		ptr->shape_color = green;
		if (ptr->adjacent != NULL) {

			adjacent_vertex* adj_ = ptr->adjacent;

			while (adj_ != NULL) {
				adj_->shape_color = red;
				ptr = &(*vertice_ptr).at(adj_->vertex_number);
				SetColor(vertice_ptr, ptr, red);
				adj_ = adj_->adjacent;
			}
		}
	}
	else if (ptr->shape_color == red&&color_ == red) {       // 情況四. ptr和從LinkList的adjacent傳下來的顏色一樣==red

	}
	else if (ptr->shape_color == green&&color_ == green) {   // 情況五. ptr和從LinkList的adjacent傳下來的顏色一樣==green

	}
	else if (ptr->shape_color == red&&color_ == green) {     // 情況六. ptr和從LinkList的adjacent傳下來的顏色不一樣
		SetBanned(vertice_ptr, ptr);
	}
	else if (ptr->shape_color == green&&color_ == red) {     // 情況七. ptr和從LinkList的adjacent傳下來的顏色不一樣
		SetBanned(vertice_ptr, ptr);
	}
	else {}                                                   // 其他情況
}
void SetBanned(vector<vertex>* vertice_ptr, struct vertex* ptr) {
	if (ptr->shape_color != banned) {
		ptr->shape_color = banned;
		if (ptr->adjacent != NULL) {

			adjacent_vertex* adj_ = ptr->adjacent;

			while (adj_ != NULL) {
				adj_->shape_color = banned;
				ptr = &(*vertice_ptr).at(adj_->vertex_number);
				SetBanned(vertice_ptr, ptr);
				adj_ = adj_->adjacent;
			}
		}
	}
	else {}
}
void SetGraph(vector<vertex>* vertice_ptr, struct vertex* ptr, int graph) {
	if (ptr->graph == -1) {
		ptr->graph = graph;
		if (ptr->adjacent != NULL) {

			adjacent_vertex* adj_ = ptr->adjacent;

			while (adj_ != NULL) {
				adj_->graph = graph;
				ptr = &(*vertice_ptr).at(adj_->vertex_number);
				SetGraph(vertice_ptr, ptr, graph);
				adj_ = adj_->adjacent;
			}
		}
	}
	else {}
}
void draw_color(
	int OMEGA,
	rect bound,
	int graph_quantity,
	vector<vertex>* vertices,
	int vertex_quantity,
	int* window_quantity_ptr,
	vector<window> windows
) {

	// initialize
	*window_quantity_ptr = ((bound.x2 - bound.x1 - 1) / OMEGA + 1)*((bound.y2 - bound.y1 - 1) / OMEGA + 1);
	vector<vector<int>> red_area(*window_quantity_ptr, vector<int>(graph_quantity));
	vector<vector<int>> green_area(*window_quantity_ptr, vector<int>(graph_quantity));
	vector<vector<int>> mix_area(*window_quantity_ptr, vector<int>(graph_quantity));
	vector<int> answer_column(graph_quantity);
	vector<int> final_answer_column(graph_quantity);
	vector<int> tmp_answer_column(graph_quantity);
	vector<window> windows_check(*window_quantity_ptr);
	set<int> uncolored_graph;
	cout << graph_quantity << endl;
	cout << *window_quantity_ptr << endl;


	for (int i = 0; i<graph_quantity; i++)
		answer_column[i] = 1;
	for (int i = 0; i<*window_quantity_ptr; i++)
		for (int j = 0; j<graph_quantity; j++) {
			red_area[i][j] = 0;
			green_area[i][j] = 0;
		}
	// calculate window positions
	{
		if ((bound.x2 - bound.x1 < OMEGA) || (bound.y2 - bound.y1 <OMEGA)) {
			cout << "crash: (bound.x2-bound.x1<OMEGA)||(bound.y2-bound.y1<OMEGA)\n";
			return;
		}
		windows.resize(*window_quantity_ptr);
		rect current;
		current.x1 = bound.x1;
		current.y1 = bound.y1;
		current.x2 = current.x1 + OMEGA;
		current.y2 = current.y1 + OMEGA;
		for (int i = 0; i < *window_quantity_ptr; i++) {
			windows[i].position = current;
			current.x1 += OMEGA;
			current.x2 += OMEGA;
			if (current.x2 > bound.x2&&current.x1 < bound.x2) {
				current.x2 = bound.x2;
				current.x1 = current.x2 - OMEGA;
			}
			else if (current.x2 > bound.x2&&current.x1 >= bound.x2) {
				current.x1 = bound.x1;
				current.x2 = current.x1 + OMEGA;
				current.y1 += OMEGA;
				current.y2 += OMEGA;
				if (current.y2 > bound.y2&&current.y1 < bound.y2) {
					current.y2 = bound.y2;
					current.y1 = current.y2 - OMEGA;
				}
			}
		}
		//for (int i = 0; i < *window_quantity_ptr; i++) {
		//	cout << windows[i].position.x1 << "  " << windows[i].position.y1 << "  " << windows[i].position.x2 << "  " << windows[i].position.y2 << "  "<<endl;
		//}
	}

	// find cross windows, and fill in color
	{
		for (int i = 0; i < vertex_quantity; i++)
			for (int j = 0; j < *window_quantity_ptr; j++) {
				int area;
				int up = min((*vertices).at(i).position.y2, windows[j].position.y2);
				int down = max((*vertices).at(i).position.y1, windows[j].position.y1);
				int right = min((*vertices).at(i).position.x2, windows[j].position.x2);
				int left = max((*vertices).at(i).position.x1, windows[j].position.x1);
				if (up > down&&right > left)
					area = (up - down)*(right - left);
				else
					area = 0;
				if ((*vertices).at(i).shape_color == red)
					red_area[j][(*vertices).at(i).graph] += area;
				else if ((*vertices).at(i).shape_color == green)
					green_area[j][(*vertices).at(i).graph] += area;
			}
	}

	// finding uncolored graph
	{
		for (int i = 0; i < vertex_quantity; i++)
			if ((*vertices).at(i).shape_color == -2)
				uncolored_graph.insert((*vertices).at(i).graph);
		set<int>::iterator it;
		for (it = uncolored_graph.begin(); it != uncolored_graph.end(); it++)
			cout << *it << " ";
		cout << endl << endl;
	}
	//system("pause");
	srand(time(NULL));
	// algorithm calculate answer_column	
	{
		// need to notice that some graph are uncolorable, that is, we only need to change the coefficient of the colorable graph.	
		for (int i = 0; i < *window_quantity_ptr; i++)
			for (int j = 0; j < graph_quantity; j++)
				mix_area[i][j] = red_area[i][j] - green_area[i][j];
		//smaller the better: different_area
		// testing different area:
		//int different_area=0;
		//for(int i=0; i<*window_quantity_ptr; i++){
		//int different_area_window=0;
		//for(int j=0; j<graph_quantity; j++)
		//different_area_window+=mix_area[i][j]*answer_column[j];
		//different_area+=abs(different_area_window);
		//}

		// answer column initialization


		{
			answer_column = vector<int>(graph_quantity, 1);
			final_answer_column = vector<int>(graph_quantity, 1);
			tmp_answer_column = vector<int>(graph_quantity, 1);
		}

		int ** mix_area_array = (int **)malloc((*window_quantity_ptr) * sizeof(int *));
		for (int i = 0; i < *window_quantity_ptr; i++) {
			mix_area_array[i] = (int *)malloc(graph_quantity * sizeof(int));
		}
		for (int i = 0; i < *window_quantity_ptr; i++) {
			for (int j = 0; j < graph_quantity; j++)
				mix_area_array[i][j] = mix_area[i][j];
		}
		int ** mix_area_array_graph = (int **)malloc(graph_quantity * sizeof(int *));
		for (int i = 0; i < graph_quantity; i++) {
			mix_area_array_graph[i] = (int *)malloc((*window_quantity_ptr) * sizeof(int));
		}
		for (int i = 0; i < *window_quantity_ptr; i++) {
			for (int j = 0; j < graph_quantity; j++)
				mix_area_array_graph[j][i] = mix_area[i][j];
		}

		int tmp_different_area = 0;
		float final_score;
		float tmp_score = 0;

		for (int d = 0; d < 1; d++) // test the probability to reach the maximun score
		{
			int iteration = 500;
			float initial_temperature = 2;
			for (int c = 0; c < iteration; c++)
			{

				for (int i = 0; i < graph_quantity; i++)
					answer_column[i] = rand() % 2 * 2 - 1;
				// try and error algorithm, simulated annealing
				float temperature;
				/*
				if (c < iteration / 2)
				temperature=initial_temperature+c;
				else
				temperature=initial_temperature+iteration-c;
				*/
				temperature = 2;
				float ratial = 0.95-float(c)/iteration*0.1;
				int count_stop = 0;
				int force_stop = 30;
				int count_force_stop = 0;
				int change_answer_graph = -1;
				int area_trace_change;
				int final_different_area;
				int* different_area_windows = (int *)malloc((*window_quantity_ptr) * sizeof(int));
				int* different_area_windows_trace = (int *)malloc((*window_quantity_ptr) * sizeof(int));
				int different_area = 0;
				for (int i = 0; i < *window_quantity_ptr; i++) {
					different_area_windows[i] = 0;
					for (int j = 0; j < graph_quantity; j++)
						different_area_windows[i] += mix_area_array[i][j] * answer_column[j];
					different_area += abs(different_area_windows[i]);
				}
				for (int i = 0; i < *window_quantity_ptr; i++) {
					different_area_windows_trace[i] = different_area_windows[i];
				}
				final_different_area = area_trace_change = different_area;
				//cout << "---------answer_column-----------" << endl;
				do {

					change_answer_graph = (change_answer_graph + 1) % graph_quantity;
					if (change_answer_graph == 0) {
						count_force_stop++;
						temperature *= ratial;
					}
					answer_column[change_answer_graph] *= -1;
					for (int i = 0; i < graph_quantity; i++)
						//cout << setw(2) << answer_column[i];
						different_area = 0;
					// old method to calculate different area
					/*
					for (int i = 0; i < *window_quantity_ptr; i++) {
						int different_area_window = 0;
						for (int j = 0; j < graph_quantity; j++)
							different_area_window += mix_area[i][j] * answer_column[j];
						different_area += abs(different_area_window);
					}
					*/
					
					if (answer_column[change_answer_graph] == 1) {
						for (int i = 0; i < *window_quantity_ptr; i++) {
							different_area_windows[i]= different_area_windows_trace[i]+2* mix_area_array_graph[change_answer_graph][i];
						}
					}
					else {
						for (int i = 0; i < *window_quantity_ptr; i++) {
							different_area_windows[i] = different_area_windows_trace[i] - 2 * mix_area_array_graph[change_answer_graph][i];
						}					
					}
					for (int i = 0; i < *window_quantity_ptr; i++) {
						different_area += abs(different_area_windows[i]);
					}

					//cout << " " << setw(7) << area_trace_change << " -> " << setw(7) << different_area;
					if (different_area < final_different_area) {
						final_different_area = different_area;
						final_answer_column = answer_column;
					}
					float possibility = exp(-(float)(different_area - area_trace_change) / OMEGA / OMEGA / 0.05 / temperature);
					//if (different_area >= area_trace_change ) {
					if (possibility < (float)(rand() % 1000) / 1000) {
						count_stop++;
						answer_column[change_answer_graph] *= -1;
						for (int i = 0; i < *window_quantity_ptr; i++) {
							different_area_windows[i] = different_area_windows_trace[i];
						}
						//cout << "        ";
					}
					else {
						count_stop = 0;
						area_trace_change = different_area;
						for (int i = 0; i < *window_quantity_ptr; i++) {
							different_area_windows_trace[i] = different_area_windows[i];
						}
						//cout << " changed";
					}
					float score = 100 - (float)area_trace_change / OMEGA / OMEGA / 0.05;
					final_score = 100 - (float)final_different_area / OMEGA / OMEGA / 0.05;
					//cout << " (" << setprecision(2) << setw(5) << score << ") , " << setprecision(2) << fixed << final_score << ", " << setprecision(2) << fixed << possibility;
					//////cout<<", >50%? ,"<<(possibility>0.5&&possibility<1);
					//////cout << ", " << temperature;
					//cout << ", " << count_force_stop;
					//cout << endl;
					//} while (count_stop < graph_quantity&&count_force_stop < force_stop);
				} while (count_force_stop < force_stop);


				if (c == 0 || final_different_area < tmp_different_area) {
					tmp_different_area = final_different_area;
					tmp_answer_column = final_answer_column;
					tmp_score = final_score;
				}

				if (c == iteration - 1) {
					final_different_area = tmp_different_area;
					final_answer_column = tmp_answer_column;
					final_score = tmp_score;
				}

				cout << tmp_score << endl;

				free(different_area_windows);
				free(different_area_windows_trace);

			}

			//cout << final_score << endl;
		}

		for (int i = 0; i < *window_quantity_ptr; i++) {
			free(mix_area_array[i]);
		}
		free(mix_area_array);
		for (int i = 0; i < *window_quantity_ptr; i++) {
			free(mix_area_array_graph[i]);
		}
		free(mix_area_array_graph);
	}

	// change the color of vertices	
	{
		for (int i = 0; i < vertex_quantity; i++)
			if (final_answer_column[(*vertices).at(i).graph] == -1)
				if ((*vertices).at(i).shape_color == red)
					(*vertices).at(i).shape_color = green;
				else if ((*vertices).at(i).shape_color == green)
					(*vertices).at(i).shape_color = red;
	}

	// calculate color density
	{
		for (int i = 0; i < *window_quantity_ptr; i++) {
			int red_area_window = 0;
			int green_area_window = 0;
			for (int j = 0; j < graph_quantity; j++)
				if (final_answer_column[j] == 1) {
					red_area_window += red_area[i][j];
					green_area_window += green_area[i][j];
				}
				else if (final_answer_column[j] == -1) {
					red_area_window += green_area[i][j];
					green_area_window += red_area[i][j];
				}
				windows[i].red_density = float(red_area_window) / OMEGA / OMEGA;
				windows[i].green_density = float(green_area_window) / OMEGA / OMEGA;
		}
	}

	/**********************test code************************/

	// check windows position with another method
	{
		int width = (bound.x2 - bound.x1 - 1) / OMEGA + 1;
		int height = (bound.y2 - bound.y1 - 1) / OMEGA + 1;
		int compare_flag = 1;
		for (int i = 0; i < *window_quantity_ptr; i++) {
			windows_check[i].position.x1 = bound.x1 + (i%width)*OMEGA;
			if (i%width == width - 1)
				windows_check[i].position.x1 = bound.x2 - OMEGA;
			windows_check[i].position.y1 = bound.y1 + (i / width)*OMEGA;
			if (i / width == height - 1)
				windows_check[i].position.y1 = bound.y2 - OMEGA;
			windows_check[i].position.x2 = windows_check[i].position.x1 + OMEGA;
			windows_check[i].position.y2 = windows_check[i].position.y1 + OMEGA;
			if (windows_check[i].position.x1 == windows[i].position.x1&&windows_check[i].position.x2 == windows[i].position.x2&&windows_check[i].position.y1 == windows[i].position.y1&&windows_check[i].position.y2 == windows[i].position.y2)
				;
			else
				compare_flag = -1;
		}
		if (compare_flag == 1)
			cout << "windows position checked OK!" << endl;
		else
			cout << "windows position checked failed." << endl;
	}

	// check windows density with another method
	{
		int compare_flag = 1;
		for (int i = 0; i < *window_quantity_ptr; i++) {
			int red_area = 0;
			int green_area = 0;
			for (int j = 0; j < vertex_quantity; j++) {
				int area;
				int up = min((*vertices).at(j).position.y2, windows[i].position.y2);
				int down = max((*vertices).at(j).position.y1, windows[i].position.y1);
				int right = min((*vertices).at(j).position.x2, windows[i].position.x2);
				int left = max((*vertices).at(j).position.x1, windows[i].position.x1);
				if (up >= down&&right >= left)
					area = (up - down + 1)*(right - left + 1);
				else
					area = 0;
				if (area > 0) {
					if ((*vertices).at(j).shape_color == red) {
						red_area += area;
					}
					else if ((*vertices).at(j).shape_color == green)
						green_area += area;
				}
			}
			windows_check[i].red_density = float(red_area) / OMEGA / OMEGA;
			windows_check[i].green_density = float(green_area) / OMEGA / OMEGA;
			if (windows_check[i].red_density == windows[i].red_density&&windows_check[i].green_density == windows[i].green_density)
				;
			else
				compare_flag = -1;
			//cout << windows_check[i].red_density <<" "<< windows[i].red_density <<" "<< windows_check[i].green_density <<" "<< windows[i].green_density<<endl;
		}
		if (compare_flag == 1)
			cout << "windows density checked OK!" << endl;
		else
			cout << "windows density checked failed." << endl;
	}

	// test score
	{
		cout << "-----------final score (each window)---------" << endl;
		float score = 100;
		for (int i = 0; i < *window_quantity_ptr; i++) {
			cout << setprecision(4) << setw(9) << windows[i].red_density << setprecision(4) << setw(9) << windows[i].green_density << endl;
			score -= abs(windows[i].red_density - windows[i].green_density) / 0.05;
		}
		cout << setprecision(4) << score << endl;
	}
}
