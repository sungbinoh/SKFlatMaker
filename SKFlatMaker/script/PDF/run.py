import os

filename = 'samplelist.txt'
#filename = 'samplelist_Private.txt'

IsPrivate = ("Private" in filename)

lines = open(filename).readlines()
pdfidshifts = open('PDFIDShift.txt').readlines()

hostname = os.environ['HOSTNAME']

os.system('mkdir -p logs')

for line in lines:

  if "#" in line:
    continue

  line = line.strip('\n')
  samplePDs = line.split("/")

  sample = samplePDs[1]

  dascmd = '/cvmfs/cms.cern.ch/common/dasgoclient --limit=1 --query="file dataset='+line+'"'
  if IsPrivate:
    dascmd = '/cvmfs/cms.cern.ch/common/dasgoclient --limit=1 --query="file dataset='+line+' instance=prod/phys03"'
  print dascmd

  os.system(dascmd+' > tmp.txt')

  filepaths = open('tmp.txt').readlines()

  if len(filepaths)==0:
    print "No file for : "+sample
    break

  filepath = filepaths[0].replace('/xrootd','').strip('\n')

  #if 'lxplus' not in hostname:
  filepath = 'root://cms-xrd-global.cern.ch/'+filepath

  cmd = 'cmsRun RunSKFlatMaker.py inputFiles='+filepath

  InShiftTxt = False
  for shiftsamples in pdfidshifts:
    words = shiftsamples.split()
    if words[0]==sample:
      InShiftTxt = True
      this_shift = words[1]
      if "?" in this_shift:
        this_shift = "0"
      cmd = cmd+' PDFIDShift='+this_shift
      break
  if not InShiftTxt:
    cmd = cmd+' PDFIDShift=0'

  if IsPrivate:
    cmd = cmd+' sampletype=PrivateMC'
  else:
    cmd = cmd+' sampletype=MC'

  final_cmd = cmd+' > logs/'+sample+'.log'
  print final_cmd
  os.system(final_cmd)

os.system('rm tmp.txt')
