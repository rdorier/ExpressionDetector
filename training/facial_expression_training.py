import os
import torch
from torchvision import datasets, transforms

# get path of the current script
script_path = os.path.realpath(__file__)
"""
Get root folder of the project
Basically files hierarchy must be like this :
ExpressionDetector
    - data
        - DatasetExpressions folder
    - training
        - training script
"""
path_parts = os.path.dirname(script_path).split('\\')[:-1]
path_parts.append('data')
path_parts.append('DataSetExpressions')
data_set_path = '\\'.join(path_parts)

transform = transforms.Compose([
    transforms.Resize(64),
    transforms.CenterCrop(64),
    transforms.ToTensor()
])

if os.path.exists(data_set_path):
    # get a dataset composed of PIl images as key, and value as class index of the target class
    facial_expression_dataset = datasets.ImageFolder(data_set_path, transform)
else:
    raise RuntimeError(f'Data set path does not exist : {data_set_path}')

# create dataloader with batch_size=32
data_loader = torch.utils.data.DataLoader(facial_expression_dataset, batch_size=32, shuffle=True)
# device configuration
device = torch.device('cuda' if torch.cuda_is_available() else 'cpu')

