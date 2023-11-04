# main.py
from openhtf.plugs.user_input import UserInput
from spintop_openhtf import TestPlan
import openhtf as htf

FORM = {
    'schema':{
        'title': "TrueFalse",
        'type': "object",
        'required': ["state"],
        'properties': {
            'state': {
                'type': "string",
                'title': "State"
            }
        }
    },
    'layout':[
        {
            "key": "state",
            "type": "radiobuttons",
            "titleMap": [
                { "value": "True", "name": "True" },
                { "value": "False", "name": "False" }
            ]
        }
    ]
}


plan = TestPlan('hello')

@plan.testcase('Hello-Test')
@plan.plug(prompts=UserInput)
@plan.measures(htf.Measurement("P4_digital")
              .doc("Pin 4 Digital Measurement")
              .equals(True))
              
def digital_read(plan, prompts):
    prompts.prompt('Hello Operator!')
    
    plan.dut_id = 'hello'
    response = prompts.prompt_form(FORM)
    
    print(response['state']);
    if(response['state'] == "True"):
        plan.measurements.P4_digital = True
    else:
        plan.measurements.P4_digital = False
    

if __name__ == '__main__':
    plan.no_trigger()
    plan.run()

#test = htf.Test(digital_read)
#test.execute()
