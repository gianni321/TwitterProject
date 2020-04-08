import json
import urllib
from urllib.request import urlopen

# Open grid file
with open("grid.txt", 'r') as f:
        grid = f.readline().split(',')

        # Move decimal place over and add negative sign if needed
        index = grid[1].find('.')
        grid1 = grid[1][0:index-2] + "." + grid[1][index-2:index] + grid[1][index+1:]
        if(grid[2] == 'S'):
                grid1 = "-" + grid1

        # Move decimal place over and add negative sign if needed
        index = grid[3].find('.')
        grid2 = grid[3][0:index-2] + "." + grid[3][index-2:index] + grid[3][index+1:]
        if(grid[4] == 'W'):
                grid2 = "-" + grid2
        
        # Combine into one grid string and call api
        grid = grid1 + ',' + grid2
        with urlopen(f"https://api.weather.gov/points/{grid}/forecast") as response:
                text = response.read()
                text = json.loads(text)
                
                # Get icon and detailed forecast
                url = text["properties"]["periods"][0]["icon"]
                report = text["properties"]["periods"][0]["detailedForecast"]

                # Write weather forecast
                with urlopen(url) as response:
                        image = response.read()
                        with open('weather_image.png', 'wb') as f:
                                f.write(image)

                # Write weather image
                with open("weather_data.txt", 'w') as f:
                        f.write(report)