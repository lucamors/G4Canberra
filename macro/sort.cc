/*
*	Sorting hit collection from G4 simulation
*
*	Energy is in keV
*	Time is in picoseconds
*
*/

struct Hit
{
	int id;
	double edep;
	double time;
};

struct Event
{
	int number;
	double energy;
	double time;
};

bool sortHit(const Hit &a, const Hit &b)
{
	return a.time < b.time;
}

void SortEvents(std::string filename)
{
	// Open ROOT file
	TFile * input_file = new TFile(filename.c_str());

	// Get TTree with Hits list
	TTree* HitList_tree = (TTree*) input_file->Get("hpge_hl");

	// Get TTree with Source time
	TTree* Source_tree  = (TTree*) input_file->Get("source_time");

	// Linking branches to variables

	double id;
	double edep, time;
	double sourcetime;

	TBranch * id_branch = HitList_tree->GetBranch("id");
	id_branch->SetAddress(&id);

	TBranch * edep_branch = HitList_tree->GetBranch("edep");
	edep_branch->SetAddress(&edep);

	TBranch * time_branch = HitList_tree->GetBranch("time");
	time_branch->SetAddress(&time);

	TBranch * sourcetime_branch = Source_tree->GetBranch("time");
	sourcetime_branch->SetAddress(&sourcetime);

	// Get number of entries
	long int nEvents = HitList_tree->GetEntries();

	// Load hits in memory
	std::vector<Hit> HitsCollection;
	Hit current_Hit = {0, 0, 0};

	for (int i = 0; i < nEvents; ++i)
	{
		id_branch->GetEntry(i);
		edep_branch->GetEntry(i);
		time_branch->GetEntry(i);

		current_Hit.id = id;
		current_Hit.edep = edep;
		current_Hit.time = time;

		HitsCollection.push_back(current_Hit);
	}

	cout << HitsCollection.size() << endl;

	// Sorting Hits collection
	std::sort(HitsCollection.begin(), HitsCollection.end(), sortHit);

	// Pack hits inside events
	std::vector<Event> EventsList;
	Event event = { 0, 0, 0};

	// Time is in ps: 10us as integration time
	double time_window = 1;

	std::vector<double> timeocc;

	for(auto hit : HitsCollection)
	{
		std::cout << hit.time << std::endl;
		if(  (hit.time-event.time) < time_window)
		{
			event.energy += hit.edep;
		}
		else
		{
			// save packed event
			EventsList.push_back(event);
			timeocc.push_back(hit.time - event.time );
			// reinit event with this hit
			event = {hit.id, hit.edep, hit.time};
			//std::cout << "Event energy : " << event.energy << std::endl;
		}
	}

	// Declaring histograms
	TH1F * h_energy      = new TH1F("h_energy","",20000, 0, 2000);
	TH1F * h_time        = new TH1F("h_time","",1000, 0, 2e13);
	TH1F * h_timesource  = new TH1F("h_sourcetime","",1000, 1e-8, 1e-3);

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 generator (seed);
	std::normal_distribution<double> distribution(0,2/2.355);
	std::cout << EventsList.size() << std::endl;
	for(size_t i = 0; i < EventsList.size(); i++)
	{
		// cout << timeocc[i] << endl;
		h_time->Fill(timeocc[i]);
		h_energy->Fill(EventsList[i].energy+distribution(generator));
	}

	double time_of_event = 0;

	for (int i = 1; i < Source_tree->GetEntries(); ++i)
	{
		sourcetime_branch->GetEntry(i);

		h_timesource->Fill(sourcetime-time_of_event);

		time_of_event = sourcetime;
	}

	TCanvas * c1 = new TCanvas();
	h_energy->Draw();

	TCanvas * c2 = new TCanvas();
	c2->Divide(2);
	c2->cd(1);
	h_time->Draw();
	c2->cd(2);
	h_timesource->Draw();

	return ;
}
