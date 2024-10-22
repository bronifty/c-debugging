exports.handler = async (event) => {
  return {
    statusCode: 200,
    body: JSON.stringify("Hello World from Tailscale-enabled Lambda!"),
  };
};
