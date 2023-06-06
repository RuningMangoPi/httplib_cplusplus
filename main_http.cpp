#include <httplib.h>

using namespace httplib;


string json_data_ = "12334";


int main(void)
{
	
	Server svr;
	svr.Post("/getTask", [&](const Request& req, Response& res) {
		auto size = req.files.size();
		auto ret1 = req.has_file("task");//判断task
		const auto& file_task = req.get_file_value("task");
		std::cout << file_task.filename << endl;
		std::cout << file_task.content_type << endl;
		std::cout << file_task.content << endl;

        auto ret2 = req.has_file("status");//判断status
		const auto& s_file = req.get_file_value("status");
		std::cout << s_file.filename << endl;
		std::cout << s_file.content_type << endl;
		std::cout << s_file.content << endl;


		if (!ret1 || !ret2){
			return res.set_content(cv::format("{\"result\": %d, \"msg\":\"%s\"}", 10001, "task/status is NULL....."), "Application/json");
		}
		else if(task!="face"){
			
			return res.set_content(cv::format("{\"result\": %d, \"msg\":\"%s task not exist.....\"}", 10002, file_task.content.c_str()), "Application/json");
		}
        
		return res.set_content(cv::format("{\"result\": %d, \"msg\":\"%s %s\"}", 10000, file_task.content.c_str(), s_file.content.c_str()), "Application/json");
		
	});

	svr.Post("/sendData", [&](const Request& req, Response& res) {

		//数据深拷贝
		char *s1;
    	const char *s2= json_data_.c_str();
    	s1=new char[strlen(s2)+1];
    	strcpy(s1,s2);

		string send_data = cv::format("{%s}", s1);
		
		return res.set_content(send_data, "Application/json");
		
	});


	svr.Post("/stop", [&](const Request& req, Response& res) {
		svr.stop();
	});

	svr.listen("0.0.0.0", 5000);
}

