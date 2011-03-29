#!/bin/bash
set -u
set -e

OUTPUT="" 

echo "cleaning ec2 node..."

ssh -i ~/ec2/Neba-Laptop.pem ubuntu@ec2-46-51-161-60.eu-west-1.compute.amazonaws.com "rm -rf ~/development/elog/*" 2>&1 $OUTPUT
echo $OUTPUT

echo "copying files to ec2 node..."

scp -r -p -i /Users/barryodriscoll/ec2/Neba-Laptop.pem /Users/barryodriscoll/Documents/crc_workspace/elog/* ubuntu@ec2-46-51-161-60.eu-west-1.compute.amazonaws.com:/home/ubuntu/development/elog 2>&1 $OUTPUT
echo $OUTPUT

echo "building and running on ec2 node..."

ssh -i ~/ec2/Neba-Laptop.pem ubuntu@ec2-46-51-161-60.eu-west-1.compute.amazonaws.com "cd /home/ubuntu/development/elog; pwd; rake build; rake run; rake test" 2>&1 $OUTPUT
echo $OUTPUT