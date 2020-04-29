import tweepy
import sys
import datetime
import json
import urllib
from urllib.request import urlopen
import auth


'''
GRV post_tweet.py.
How TO Run: $python post_tweet.py 
This program needs a file named grids.txt to run
This is the format this program can parse 
$GPGLL,4036.05215,N,10504.19257,W,220029.00,A,A*7A
Pass in a file that has the contents of what should be tweeted out.
The current date will be appended to the begining of the tweet.
@WARNING This code will not be able to post the same status twice. @Fix by adding in date.
'''


def parse_weather(grid):
    # string that will contain current weather information
    weather_report = "No current weather information at this location."

    grid = grid.split(' ')
    latitude = grid[0]
    longitude = grid[2]

    if(grid[1] == 'S'):
        latitude = "-" + latitude

    # Move decimal place over and add negative sign if needed
    if(grid[3] == 'W'):
        longitude = "-" + longitude

    # Combine into one grid string and call api
    grid = latitude + ',' + longitude

    with urlopen(f"https://api.weather.gov/points/{grid}/forecast") as response:
        text = response.read()
        text = json.loads(text)

        # Get icon and detailed forecast
        image_url = text["properties"]["periods"][0]["icon"][:-6]+"large"
        weather_report = "Cords: " + str(grid) + " \n"
        weather_report += "Temp: " + \
            str(text["properties"]["periods"][0]["temperature"]) + " F\n"
        weather_report += "Forecast: " + \
            text["properties"]["periods"][0]["shortForecast"]

        # Write weather image
        with urlopen(image_url) as response:
            image = response.read()
            with open('weather_image.png', 'wb') as f:
                f.write(image)

        # # Write weather forecast
        # with open("weather_data.txt", 'w') as f:
        #     f.write(report)
    return weather_report


def post_tweet(tweet, id):
    # Twitter Tokens
    api = auth.getAuth()

    # Seting "@var tweet" to be posted as status.

    # Getting picture
    media = api.media_upload("weather_image.png")

    # Sending
    # if(id == 0):
    status = api.update_status(status=tweet, media_ids=[media.media_id])
    # else:
    #     status = api.update_status(status=tweet, media_ids=[
    #                                media.media_id], in_reply_to_status_id=id)


if __name__ == "__main__":
    # Open grid file
    grid = str(sys.argv[1])
    id = 0
    if (len(sys.argv) > 2):
        id = sys.argv[2]

    # Pull out a parsed message
    contents = parse_weather(grid)

    # Get date
    now = datetime.datetime.now()
    # Format date
    now = now.strftime("%Y-%m-%d %H:%M")
    # Show what will be printed (May need to be removed)
    print("This is the content that will be tweeted out: " +
          str(now) + "\n" + contents)
    # Load into our post tweet with date
    tweet = str(now) + "\n" + contents
    post_tweet(tweet, id)
