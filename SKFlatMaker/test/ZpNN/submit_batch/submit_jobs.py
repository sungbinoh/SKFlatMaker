import os
import datetime
import subprocess
import time

copy_proxy = "cp /tmp/x509up_u41043 ./scripts"
os.system(copy_proxy)

now = datetime.datetime.now()
temp_dir = "temp_" + str(now.month) + "_" + str(now.day) + "_" + str(now.hour) + "_" + str(now.minute)

make_tmp_dir = "mkdir " + temp_dir
os.system(make_tmp_dir)

a = 0
f = open("../filelist_Zprime_miniaod.txt", 'r')
for line in f: # -- loop over mass points 
    if not line: break
    line = line[0:-1]
    mass_point = line.split("/")[1]
    # -- check output directory
    out_dir_exists = os.path.isdir("/pnfs/knu.ac.kr/data/cms/store/user/suoh/SKFlat/2016/Private/Run2Legacy_v1/" + mass_point)
    if not out_dir_exists:
        os.system("mkdir /pnfs/knu.ac.kr/data/cms/store/user/suoh/SKFlat/2016/Private/Run2Legacy_v1/" + mass_point)
   
    # -- making dir of each mass point & copy scripts
    os.system("mkdir ./" + temp_dir + "/" + mass_point)
    os.system("cp scripts/* ./" + temp_dir + "/"+ mass_point)
    os.system("cp ../lists/" + mass_point + "_list.txt ./" + temp_dir + "/" + mass_point + "/list.txt")
    os.chdir("./" + temp_dir + "/"+ mass_point)
    short_mass_point = mass_point[11:-11]
    change_temp_dir = "find ./. -name run.sh -type f -exec sed -i s/temp_dir/" + temp_dir + "/g {} +"
    change_mass_point = "find ./. -name run.sh -type f -exec sed -i s/mass_point/" + mass_point + "/g {} +"
    os.system(change_temp_dir)
    os.system(change_mass_point)

    # -- Loop over input file list of each mass point
    file_list = open("./list.txt", 'r')
    job_number = 0
    for input_file in file_list:
        os.system("mkdir job_" + str(job_number))
        os.chdir("./job_" + str(job_number))
        os.system("cp ../run.sh .")
        os.system("cp ../RunSKFlatMaker.py .")
        current_dir = os.getcwd()
        # -- Add lines on run.sh
        file_run = open("run.sh", 'a') 
        file_run.write("\n" + "cd " + current_dir + "\n")
        file_run.write("cmsRun RunSKFlatMaker.py year=2016 sampletype=PrivateMC ScaleIDRange=1001,1009 PDFErrorIDRange=1010,1110 PDFAlphaSIDRange=1111,1112 PDFAlphaSScaleValue=0.75,0.75 inputFiles=")
        input_file = input_file[0:-1]
        file_run.write(input_file)
        file_run.write(" outputFile=SKFlatNtuple_2016_MC_" + str(job_number) + ".root &> log_" + str(job_number) + ".log")
        file_run.write(
'''\n
SumError=999
Trial=0

while [ \"$SumError\" -ne 0 ]; do
  if [ \"$Trial\" -gt 9999 ]; then
    break
  fi
  xrdcp SKFlatNtuple_2016_MC_''' + str(job_number) + '''.root root://cluster142.knu.ac.kr//store/user/suoh/SKFlat/2016/Private/Run2Legacy_v1/''' + mass_point + '''/SKFlatNtuple_2016_MC_''' + str(job_number) + '''.root &> copylog_''' + str(job_number) + '''.log \n

  # Run: [ERROR] Server responded with an error: [3012] Internal timeout
  N_ERROR=`grep \"ERROR\" copylog_0.log -R | wc -l`
  N_timeout=`grep \"timeout\" copylog_0.log -R | wc -l`
  # Run: [FATAL] Auth failed
  N_FATAL=`grep \"FATAL\" copylog_0.log -R | wc -l`

  SumError=$(($N_ERROR + $N_timeout + $N_FATAL))

  if [ \"$SumError\" -ne 0 ]; then
    echo \"SumError=\"$SumError
    echo \"Error occured.. running again in 30 seconds..\"
    Trial=$((Trial+=1))
    sleep 30
  fi

done
rm SKFlatNtuple_2017_MC_''' + str(job_number) + '''.root''')
        file_run.close()
        
        # -- Submit Job
        submit_job = "qsub -q cms -N " + short_mass_point + "_" + str(job_number)+ " -V run.sh"
        os.system(submit_job)
        job_number = job_number + 1
        os.chdir("../")

    ## -- Preventing too much jobs ( < 1000)
    too_much_jobs = True
    while too_much_jobs:
        p = subprocess.Popen(["myqstat"], stdout=subprocess.PIPE)
        out = p.stdout.read()
        job_stat=out.split(" ")
        total_jobs_str = job_stat[2]
        total_jobs_str = total_jobs_str[0:-1]
        print total_jobs_str
        total_jobs = int(total_jobs_str)
        if total_jobs < 1000:
            too_much_jobs = False
        if total_jobs > 1000:
            time.sleep(300)
            
        
    os.chdir("../../")
    
    #abort for test
    #a = a + 1
    #if a > 5:
    #    break
f.close()
